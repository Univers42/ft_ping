/* ************************************************************************** */
/*   test_fixes.c — asserts the CORRECTED behaviour of the libft bugs fixed   */
/*   on 2026-06-05. Runs under both allocators (libc≡ft) and must not leak.    */
/* ************************************************************************** */

#include "libft_test.h"

/* ft_strncasecmp: n==0 must return 0; must compare exactly n bytes, case-fold */
static void	test_strncasecmp(void)
{
	t_check_int("ncasecmp_n0", ft_strncasecmp("abc", "xyz", 0), 0);
	t_check("ncasecmp_eq5", ft_strncasecmp("Hello!", "hElLo?", 5) == 0);
	t_check("ncasecmp_diff", ft_strncasecmp("abc", "abd", 5) != 0);
	t_check("ncasecmp_case", ft_strncasecmp("ABC", "abc", 3) == 0);
	t_check("ncasecmp_long", ft_strncasecmp("abc", "abc", 100) == 0);
	t_check("ncasecmp_prefix", ft_strncasecmp("abcX", "abcY", 3) == 0);
}

/* ft_lstclear: NULL pointers must be no-ops, not crashes */
static void	test_lstclear_null(void)
{
	t_list	*empty;

	ft_lstclear(NULL, fn_free);
	empty = NULL;
	ft_lstclear(&empty, fn_free);
	t_check("lstclear_null_safe", 1);
	t_check("lstclear_empty_null", empty == NULL);
}

/* fn_realloc3: new_cap==0 frees and returns NULL; grow preserves prefix;
   NULL ptr acts as malloc; old buffer always released (leak oracle verifies) */
static void	test_realloc3(void)
{
	char	*p;
	char	*q;

	p = (char *)fn_malloc(16);
	ft_memcpy(p, "ABCDEFGHIJKLMNO", 16);
	q = (char *)fn_realloc3(p, 16, 64);
	t_check_nonnull("realloc3_grow", q);
	t_check_mem("realloc3_prefix", q, "ABCDEFGHIJKLMNO", 16);
	fn_free(q);
	p = (char *)fn_malloc(32);
	q = (char *)fn_realloc3(p, 32, 0);
	t_check("realloc3_zero_null", q == NULL);
	q = (char *)fn_realloc3(NULL, 0, 48);
	t_check_nonnull("realloc3_as_malloc", q);
	fn_free(q);
}

/* ft_strnstr: NULL-guarded; still finds within bound */
static void	test_strnstr(void)
{
	t_check("strnstr_null_hay", ft_strnstr(NULL, "x", 5) == NULL);
	t_check("strnstr_null_needle", ft_strnstr("hay", NULL, 5) == NULL);
	t_check("strnstr_find", ft_strnstr("hayneedle", "needle", 100) != NULL);
	t_check("strnstr_bound", ft_strnstr("hayneedle", "needle", 4) == NULL);
	t_check_str("strnstr_empty", ft_strnstr("abc", "", 3), "abc");
}

/* vec_push_int: vec_init then vec_push_int (NO manual elem_size) must round-trip
   ints correctly — this is the regression the fix addresses. */
static void	test_vec_push_int(void)
{
	t_vec	v;
	int		i;
	int		*got;
	int		ok;

	vec_init(&v);
	i = 0;
	while (i < 256)
	{
		vec_push_int(&v, i * 7 - 3);
		i++;
	}
	t_check_int("vec_pushint_len", (long)v.len, 256);
	ok = 1;
	i = 0;
	while (i < 256)
	{
		got = (int *)vec_idx(&v, (size_t)i);
		if (!got || *got != i * 7 - 3)
			ok = 0;
		i++;
	}
	t_check("vec_pushint_roundtrip", ok);
	vec_destroy(&v, NULL);
}

/* array_reference: previously crashed (NULL lastref) after sequential inserts.
   Now it must return the value at each index without crashing. */
static void	test_array_reference(void)
{
	t_arr	*a;
	int		i;
	char	*exp;
	int		ok;

	a = array_create();
	t_check_nonnull("array_create", a);
	if (!a)
		return ;
	i = -1;
	while (++i < 64)
		array_insert(a, (size_t)i, ft_itoa(i));
	ok = 1;
	i = -1;
	while (++i < 64)
	{
		exp = ft_itoa(i);
		if (!array_reference(a, (size_t)i) || !exp
			|| ft_strcmp(array_reference(a, (size_t)i), exp) != 0)
			ok = 0;
		fn_free(exp);
	}
	t_check("array_reference_seq", ok);
	array_dispose(a);
}

static void	make_key(char *buf, int n)
{
	char	*s;

	s = ft_itoa(n);
	buf[0] = 'k';
	ft_strlcpy(buf + 1, s, 30);
	fn_free(s);
}

/* hash now OWNS a copy of the key: reusing the SAME stack buffer for every
   insert must still yield 200 distinct, retrievable entries. */
static void	test_hash_stack_key(void)
{
	t_hash	h;
	char	buf[32];
	int		i;
	int		ok;

	t_check("hash_init", hash_init(&h, 8));
	i = -1;
	while (++i < 200)
	{
		make_key(buf, i);
		hash_set(&h, buf, (void *)(long)(i + 1));
	}
	ok = 1;
	i = -1;
	while (++i < 200)
	{
		make_key(buf, i);
		if (hash_get(&h, buf) != (void *)(long)(i + 1))
			ok = 0;
	}
	t_check("hash_stack_key_copy", ok);
	hash_destroy(&h, NULL);
}

/* ft_sstrdup must now return fn_*-heap memory (freeable with fn_free), not a
   bump-allocated arena pointer that would corrupt on fn_free. */
static void	test_sstrdup(void)
{
	char	*s;

	s = ft_sstrdup("arena-no-more");
	t_check_str("sstrdup", s, "arena-no-more");
	fn_free(s);
}

int	main(void)
{
	t_begin("fixes");
	test_sstrdup();
	test_strncasecmp();
	test_lstclear_null();
	test_realloc3();
	test_strnstr();
	test_vec_push_int();
	test_array_reference();
	test_hash_stack_key();
	return (t_end());
}
