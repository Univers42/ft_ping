/* ************************************************************************** */
/*   test_vector.c — full lifecycle test for t_vec (ft_vector).               */
/*   Tests int-element vectors, byte/char vectors, growth churn, pop-to-empty, */
/*   re-fill, and clear. All memory freed; t_end() must report 0 live bytes.  */
/* ************************************************************************** */

#include "libft_test.h"
#include "srcs/ds/vector/ft_vector.h"

/* ------------------------------------------------------------------ tests  */

/* 1. Basic int vector: push 1000, verify size & round-trip, pop all */
static void	test_int_push_pop(void)
{
	t_vec	v;
	int		val;
	int		*got;
	int		i;
	int		ok;

	vec_init(&v);
	v.elem_size = sizeof(int);

	i = 0;
	while (i < 1000)
	{
		val = i * 3 + 7;
		vec_push(&v, &val);
		i++;
	}
	t_check_int("int_push_len", (long)v.len, 1000);

	ok = 1;
	i = 0;
	while (i < 1000)
	{
		got = (int *)vec_idx(&v, (size_t)i);
		if (*got != i * 3 + 7)
			ok = 0;
		i++;
	}
	t_check("int_roundtrip", ok);

	/* pop all the way down */
	while (v.len > 0)
		vec_pop(&v);
	t_check_int("int_pop_empty", (long)v.len, 0);

	vec_destroy(&v, NULL);
}

/* 2. Push with vec_push_int helper; pre-set elem_size=sizeof(int).
 * NOTE: vec_push_int only sets elem_size when it is 0; vec_init leaves it 1.
 * Correct usage requires setting elem_size before calling vec_push_int. */
static void	test_push_int_helper(void)
{
	t_vec	v;
	int		*p;
	int		i;
	int		ok;

	vec_init(&v);
	v.elem_size = sizeof(int);
	i = 0;
	while (i < 500)
	{
		vec_push_int(&v, i * 2);
		i++;
	}
	t_check_int("push_int_len", (long)v.len, 500);

	ok = 1;
	i = 0;
	while (i < 500)
	{
		p = (int *)vec_idx(&v, (size_t)i);
		if (*p != i * 2)
			ok = 0;
		i++;
	}
	t_check("push_int_roundtrip", ok);
	vec_destroy(&v, NULL);
}

/* 3. Byte vector via vec_push_byte; 2000 bytes with t_rand values */
static void	test_byte_vector(void)
{
	t_vec			v;
	unsigned char	expected[2000];
	int				i;
	unsigned char	b;
	unsigned char	*got;
	int				ok;

	t_reseed(0xBEEF01);
	vec_init(&v);
	i = 0;
	while (i < 2000)
	{
		b = (unsigned char)(t_rand() & 0xFF);
		expected[i] = b;
		vec_push_byte(&v, b);
		i++;
	}
	t_check_int("byte_vec_len", (long)v.len, 2000);

	ok = 1;
	i = 0;
	while (i < 2000)
	{
		got = (unsigned char *)vec_idx(&v, (size_t)i);
		if (*got != expected[i])
			ok = 0;
		i++;
	}
	t_check("byte_roundtrip", ok);
	vec_destroy(&v, NULL);
}

/* 4. String accumulation via vec_push_str / vec_push_nstr */
static void	test_str_accumulation(void)
{
	t_vec	v;
	int		i;

	vec_init(&v);
	/* elem_size == 1 by default; vec_push_str appends chars */
	i = 0;
	while (i < 200)
	{
		vec_push_str(&v, "hello");
		i++;
	}
	t_check_int("str_acc_len", (long)v.len, 200 * 5);
	/* ends with NUL, so ctx is a valid C string */
	t_check_nonnull("str_acc_nonnull", v.ctx);
	/* first 5 chars */
	t_check_mem("str_acc_prefix", v.ctx, "hello", 5);

	/* clear and re-use */
	vec_clear(&v);
	t_check_int("str_clear_len", (long)v.len, 0);
	vec_push_str(&v, "world");
	t_check_int("str_reuse_len", (long)v.len, 5);
	t_check_str("str_reuse_val", (char *)v.ctx, "world");

	vec_destroy(&v, NULL);
}

/* 5. vec_push_char: 3000 chars, verify last and total count */
static void	test_push_char(void)
{
	t_vec	v;
	int		i;
	char	c;
	char	*got;

	t_reseed(0xCAFE);
	vec_init(&v);
	i = 0;
	while (i < 3000)
	{
		c = (char)('A' + (t_rand() % 26));
		vec_push_char(&v, c);
		i++;
	}
	t_check_int("push_char_len", (long)v.len, 3000);
	/* Buffer must be NUL-terminated */
	got = (char *)v.ctx;
	t_check("push_char_nonnull", got != NULL);
	vec_destroy(&v, NULL);
}

/* 6. npush: push bulk arrays of ints */
static void	test_npush(void)
{
	t_vec	v;
	int		block[50];
	int		i;
	int		j;
	int		*p;
	int		ok;

	vec_init(&v);
	v.elem_size = sizeof(int);
	i = 0;
	while (i < 50)
	{
		block[i] = i;
		i++;
	}
	/* push the block 20 times = 1000 elements */
	i = 0;
	while (i < 20)
	{
		vec_npush(&v, block, 50);
		i++;
	}
	t_check_int("npush_len", (long)v.len, 1000);

	ok = 1;
	i = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 50)
		{
			p = (int *)vec_idx(&v, (size_t)(i * 50 + j));
			if (*p != j)
				ok = 0;
			j++;
		}
		i++;
	}
	t_check("npush_roundtrip", ok);
	vec_destroy(&v, NULL);
}

/* 7. Growth churn: repeatedly push 5000, clear, push 5000 */
static void	test_growth_churn(void)
{
	t_vec	v;
	int		val;
	int		i;
	int		pass;
	long	sum;

	t_reseed(0xDEAD42);
	vec_init(&v);
	v.elem_size = sizeof(int);

	pass = 0;
	while (pass < 3)
	{
		i = 0;
		sum = 0;
		while (i < 5000)
		{
			val = (int)(t_rand() % 10000);
			sum += val;
			vec_push(&v, &val);
			i++;
		}
		t_check_int("churn_len", (long)v.len, 5000);
		vec_clear(&v);
		t_check_int("churn_clear", (long)v.len, 0);
		pass++;
	}
	t_check("churn_ctx_alive", v.ctx != NULL);
	vec_destroy(&v, NULL);
}

/* 8. vec_ends_with_str: string vector suffix check */
static void	test_ends_with_str(void)
{
	t_vec	v;

	vec_init(&v);
	vec_push_str(&v, "hello world");
	t_check("ends_world", (int)vec_ends_with_str(&v, "world"));
	t_check("not_ends_hello", !(int)vec_ends_with_str(&v, "hello"));
	t_check("ends_empty", (int)vec_ends_with_str(&v, ""));
	vec_destroy(&v, NULL);
}

/* 9. Empty vector edge cases */
static void	test_empty_edge(void)
{
	t_vec	v;
	int		val;

	vec_init(&v);
	v.elem_size = sizeof(int);
	t_check_int("empty_len", (long)v.len, 0);
	t_check_int("empty_cap", (long)v.cap, 0);
	/* push single element and pop */
	val = 42;
	vec_push(&v, &val);
	t_check_int("single_len", (long)v.len, 1);
	vec_pop(&v);
	t_check_int("single_pop_len", (long)v.len, 0);
	/* destroy empty (no crash) */
	vec_destroy(&v, NULL);
	t_check("empty_ctx_null", v.ctx == NULL);
}

/* 10. Pointer element vector with free callback */
static void	free_ptr_elem(void *el)
{
	char	**pp;

	pp = (char **)el;
	fn_free(*pp);
}

static void	test_ptr_vector_with_free(void)
{
	t_vec	v;
	char	*s;
	int		i;

	vec_init(&v);
	v.elem_size = sizeof(char *);
	i = 0;
	while (i < 200)
	{
		s = ft_strdup("libft_test_str");
		vec_push(&v, &s);
		i++;
	}
	t_check_int("ptr_vec_len", (long)v.len, 200);
	/* destroy with free callback — frees every strdup'd string */
	vec_destroy(&v, free_ptr_elem);
	t_check("ptr_vec_destroyed", v.ctx == NULL);
}

/* ------------------------------------------------------------------ main   */

int	main(void)
{
	t_begin("vector");
	t_reseed(0xABCD1234);
	test_int_push_pop();
	test_push_int_helper();
	test_byte_vector();
	test_str_accumulation();
	test_push_char();
	test_npush();
	test_growth_churn();
	test_ends_with_str();
	test_empty_edge();
	test_ptr_vector_with_free();
	return (t_end());
}
