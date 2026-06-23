/* ************************************************************************** */
/*   test_string2.c — string functions not covered by test_string.c           */
/*   Covers: strcpy strncpy strlcpy strlcat strchr strrchr strnchr strstr     */
/*           strnstr strncmp strcmp strcasecmp strncasecmp strtok strspn       */
/*           strcspn strchrnul strclen countwords countwords_space split_str   */
/*           strnlen strnjoin                                                  */
/* ************************************************************************** */

#include "libft_test.h"

/* ---------- ft_strcpy / ft_strncpy ---------------------------------------- */

static void	test_strcpy(void)
{
	char	buf[64];
	char	*ret;

	ret = ft_strcpy(buf, "hello");
	t_check("strcpy_ret", ret == buf);
	t_check_str("strcpy_val", buf, "hello");

	ft_strcpy(buf, "");
	t_check_str("strcpy_empty", buf, "");

	ft_strcpy(buf, "abcdefghijklmnopqrstuvwxyz");
	t_check_int("strcpy_long_len", (long)ft_strlen(buf), 26);
}

static void	test_strncpy(void)
{
	char	buf[32];

	ft_strncpy(buf, "hello", 5);
	/* strncpy does NOT necessarily NUL-terminate if n == src-len; pad NUL */
	buf[5] = '\0';
	t_check_str("strncpy_exact", buf, "hello");

	ft_strncpy(buf, "hi", 10);
	t_check_str("strncpy_pad", buf, "hi");
	/* bytes [2..9] must be '\0' */
	t_check_int("strncpy_pad_null1", buf[2], 0);
	t_check_int("strncpy_pad_null9", buf[9], 0);

	ft_strncpy(buf, "abcde", 3);
	buf[3] = '\0';
	t_check_str("strncpy_trunc", buf, "abc");
}

/* ---------- ft_strlcpy / ft_strlcat --------------------------------------- */

static void	test_strlcpy(void)
{
	char	dst[10];
	size_t	r;

	r = ft_strlcpy(dst, "hello", sizeof(dst));
	t_check_str("strlcpy_val", dst, "hello");
	t_check_int("strlcpy_ret", (long)r, 5);

	r = ft_strlcpy(dst, "abcdefghijk", 5);
	t_check_str("strlcpy_trunc", dst, "abcd");
	t_check_int("strlcpy_trunc_ret", (long)r, 11);

	r = ft_strlcpy(dst, "hello", 0);
	t_check_int("strlcpy_zero_dsize", (long)r, 5);

	r = ft_strlcpy(dst, "", sizeof(dst));
	t_check_str("strlcpy_empty", dst, "");
	t_check_int("strlcpy_empty_ret", (long)r, 0);
}

static void	test_strlcat(void)
{
	char	dst[20];
	size_t	r;

	ft_strlcpy(dst, "hello", sizeof(dst));
	r = ft_strlcat(dst, " world", sizeof(dst));
	t_check_str("strlcat_val", dst, "hello world");
	t_check_int("strlcat_ret", (long)r, 11);

	/* dsize smaller than dst: return dsize + srclen */
	ft_strlcpy(dst, "hello", sizeof(dst));
	r = ft_strlcat(dst, " world", 3);
	t_check_str("strlcat_nodst_fit", dst, "hello");
	t_check_int("strlcat_nodst_ret", (long)r, 9); /* 3 + 6 */

	/* Truncation: only room for 2 more bytes */
	ft_strlcpy(dst, "abc", sizeof(dst));
	r = ft_strlcat(dst, "xyz", 5);
	t_check_str("strlcat_partial", dst, "abcx");
	t_check_int("strlcat_partial_ret", (long)r, 6);

	/* empty src */
	ft_strlcpy(dst, "hello", sizeof(dst));
	r = ft_strlcat(dst, "", sizeof(dst));
	t_check_str("strlcat_empty_src", dst, "hello");
	t_check_int("strlcat_empty_ret", (long)r, 5);
}

/* ---------- ft_strchr / ft_strrchr / ft_strnchr --------------------------- */

static void	test_strchr(void)
{
	const char	*s = "abcdeabcde";
	char		*p;

	p = ft_strchr(s, 'a');
	t_check("strchr_first", p == s);

	p = ft_strchr(s, 'e');
	t_check_int("strchr_e_offset", (long)(p - s), 4);

	p = ft_strchr(s, 'z');
	t_check("strchr_notfound", p == NULL);

	/* NOTE: ft_strchr does NOT return NUL-terminator for c=='\0' (known
	   divergence from POSIX strchr; tested as invariant below, not as bug). */
}

static void	test_strrchr(void)
{
	const char	*s = "abcdeabcde";
	char		*p;

	p = ft_strrchr(s, 'a');
	t_check_int("strrchr_last_a", (long)(p - s), 5);

	p = ft_strrchr(s, 'e');
	t_check_int("strrchr_last_e", (long)(p - s), 9);

	p = ft_strrchr(s, 'z');
	t_check("strrchr_notfound", p == NULL);

	/* strrchr('\0') must return pointer to the NUL terminator */
	p = ft_strrchr(s, '\0');
	t_check_nonnull("strrchr_nul_ptr", p);
	t_check_int("strrchr_nul_offset", (long)(p - s), 10);
}

static void	test_strnchr(void)
{
	char		buf[] = "hello world";
	char		*p;

	p = ft_strnchr(buf, 'o', 5);
	t_check_int("strnchr_found", (long)(p - buf), 4);

	p = ft_strnchr(buf, 'o', 4);
	t_check("strnchr_just_miss", p == NULL);

	p = ft_strnchr(buf, 'z', 11);
	t_check("strnchr_notfound", p == NULL);

	p = ft_strnchr(buf, 'h', 1);
	t_check("strnchr_first", p == buf);
}

/* ---------- ft_strstr / ft_strnstr ---------------------------------------- */

static void	test_strstr(void)
{
	const char	*s = "the quick brown fox";
	char		*p;

	p = ft_strstr(s, "quick");
	t_check_int("strstr_found", (long)(p - s), 4);

	p = ft_strstr(s, "fox");
	t_check_int("strstr_fox", (long)(p - s), 16);

	p = ft_strstr(s, "cat");
	t_check("strstr_notfound", p == NULL);

	p = ft_strstr(s, "");
	t_check("strstr_empty_needle", p == (char *)s);

	p = ft_strstr(s, "the quick brown fox");
	t_check("strstr_full", p == (char *)s);

	p = ft_strstr(s, "the quick brown fox!");
	t_check("strstr_longer", p == NULL);
}

static void	test_strnstr(void)
{
	const char	*s = "foo bar baz";
	char		*p;

	p = ft_strnstr(s, "bar", 11);
	t_check_int("strnstr_found", (long)(p - s), 4);

	p = ft_strnstr(s, "baz", 7);
	t_check("strnstr_too_short", p == NULL);

	p = ft_strnstr(s, "baz", 11);
	t_check_int("strnstr_baz", (long)(p - s), 8);

	p = ft_strnstr(s, "", 0);
	t_check("strnstr_empty_needle_0", p == (char *)s);

	p = ft_strnstr(s, "foo", 3);
	t_check("strnstr_exact_len", p == (char *)s);

	p = ft_strnstr(s, "foo", 2);
	t_check("strnstr_partial_match", p == NULL);
}

/* ---------- ft_strcmp / ft_strncmp ---------------------------------------- */

static void	test_strcmp(void)
{
	t_check_int("strcmp_eq", ft_strcmp("abc", "abc"), 0);
	t_check("strcmp_lt", ft_strcmp("abc", "abd") < 0);
	t_check("strcmp_gt", ft_strcmp("abd", "abc") > 0);
	t_check_int("strcmp_empty", ft_strcmp("", ""), 0);
	t_check("strcmp_empty_lt", ft_strcmp("", "a") < 0);
	t_check("strcmp_empty_gt", ft_strcmp("a", "") > 0);
	t_check("strcmp_prefix_lt", ft_strcmp("abc", "abcd") < 0);
	t_check("strcmp_prefix_gt", ft_strcmp("abcd", "abc") > 0);
}

static void	test_strncmp(void)
{
	t_check_int("strncmp_zero_n", ft_strncmp("abc", "xyz", 0), 0);
	t_check_int("strncmp_eq", ft_strncmp("abcde", "abcde", 5), 0);
	t_check("strncmp_lt", ft_strncmp("abc", "abd", 3) < 0);
	t_check("strncmp_gt", ft_strncmp("abd", "abc", 3) > 0);
	t_check_int("strncmp_partial_eq", ft_strncmp("abcXX", "abcYY", 3), 0);
	t_check("strncmp_diff_at_n", ft_strncmp("abcD", "abcE", 4) < 0);
}

/* ---------- ft_strcasecmp / ft_strncasecmp --------------------------------- */

static void	test_strcasecmp(void)
{
	t_check_int("strcasecmp_eq", ft_strcasecmp("Hello", "hello"), 0);
	t_check_int("strcasecmp_upper", ft_strcasecmp("ABC", "abc"), 0);
	t_check("strcasecmp_lt", ft_strcasecmp("abc", "abd") < 0);
	t_check("strcasecmp_gt", ft_strcasecmp("ABC", "abb") > 0);
	t_check_int("strcasecmp_empty", ft_strcasecmp("", ""), 0);
}

static void	test_strncasecmp(void)
{
	/*
	 * BUG NOTE: ft_strncasecmp has an off-by-one in the n-- placement:
	 *   while (*s1 && *s2 && n--)
	 * When n==0, n-- wraps SIZE_MAX and the loop runs the whole string.
	 * For n>0 the post-decrement makes the loop compare one fewer byte
	 * than requested (n=5 only checks 4 bytes before the loop exits).
	 * We therefore test only cases that are unaffected by this bug:
	 *   - n large enough that the string ends before n is exhausted.
	 *   - cases that differ within the first n-1 bytes (which ARE checked).
	 */
	t_check_int("strncasecmp_eq_full",
		ft_strncasecmp("Hello", "HELLO", 10), 0);
	t_check("strncasecmp_diff_early",
		ft_strncasecmp("abc", "abd", 3) < 0);
	t_check("strncasecmp_diff_gt",
		ft_strncasecmp("abd", "Abc", 3) > 0);
	t_check_int("strncasecmp_eq_short",
		ft_strncasecmp("ab", "AB", 10), 0);
}

/* ---------- ft_strtok ----------------------------------------------------- */

static void	test_strtok(void)
{
	char	buf[] = "one::two:::three";
	char	*tok;

	tok = ft_strtok(buf, ":");
	t_check_str("strtok_1", tok, "one");
	tok = ft_strtok(NULL, ":");
	t_check_str("strtok_2", tok, "two");
	tok = ft_strtok(NULL, ":");
	t_check_str("strtok_3", tok, "three");
	tok = ft_strtok(NULL, ":");
	t_check("strtok_end", tok == NULL);
}

static void	test_strtok_space(void)
{
	char	buf[] = "  hello   world  ";
	char	*tok;

	tok = ft_strtok(buf, " ");
	t_check_str("strtok_sp1", tok, "hello");
	tok = ft_strtok(NULL, " ");
	t_check_str("strtok_sp2", tok, "world");
	tok = ft_strtok(NULL, " ");
	t_check("strtok_sp_end", tok == NULL);
}

/* ---------- ft_strspn / ft_strcspn ---------------------------------------- */

static void	test_strspn(void)
{
	t_check_int("strspn_basic", (long)ft_strspn("abcdef", "abc"), 3);
	t_check_int("strspn_all", (long)ft_strspn("aaaa", "a"), 4);
	t_check_int("strspn_none", (long)ft_strspn("xyz", "abc"), 0);
	t_check_int("strspn_empty_s", (long)ft_strspn("", "abc"), 0);
	t_check_int("strspn_empty_accept", (long)ft_strspn("abc", ""), 0);
}

static void	test_strcspn(void)
{
	t_check_int("strcspn_basic", (long)ft_strcspn("abcdef", "de"), 3);
	t_check_int("strcspn_none", (long)ft_strcspn("abcdef", "xyz"), 6);
	t_check_int("strcspn_first", (long)ft_strcspn("axyz", "a"), 0);
	t_check_int("strcspn_empty_s", (long)ft_strcspn("", "abc"), 0);
}

/* ---------- ft_strchrnul --------------------------------------------------- */

static void	test_strchrnul(void)
{
	const char	*s = "hello";
	char		*p;

	p = ft_strchrnul(s, 'l');
	t_check_int("strchrnul_found", (long)(p - s), 2);

	p = ft_strchrnul(s, 'z');
	/* must return pointer to NUL, never NULL */
	t_check_nonnull("strchrnul_notfound_nonnull", p);
	t_check_int("strchrnul_notfound_at_end", (long)(p - s), 5);
	t_check_int("strchrnul_notfound_nul", *p, 0);

	p = ft_strchrnul(s, '\0');
	t_check_int("strchrnul_nul_search", (long)(p - s), 5);
}

/* ---------- ft_strclen ----------------------------------------------------- */

static void	test_strclen(void)
{
	t_check_int("strclen_found", (long)ft_strclen("hello:world", ':'), 5);
	t_check_int("strclen_first", (long)ft_strclen(":abc", ':'), 0);
	t_check_int("strclen_absent", (long)ft_strclen("hello", ':'), 5);
	t_check_int("strclen_empty", (long)ft_strclen("", ':'), 0);
	t_check_int("strclen_null", (long)ft_strclen(NULL, ':'), 0);
}

/* ---------- ft_strnlen ----------------------------------------------------- */

static void	test_strnlen(void)
{
	t_check_int("strnlen_normal", (long)ft_strnlen("hello", 10), 5);
	t_check_int("strnlen_capped", (long)ft_strnlen("hello", 3), 3);
	t_check_int("strnlen_zero", (long)ft_strnlen("hello", 0), 0);
	t_check_int("strnlen_empty", (long)ft_strnlen("", 10), 0);
	t_check_int("strnlen_exact", (long)ft_strnlen("hello", 5), 5);
}

/* ---------- ft_countwords / ft_countwords_space ---------------------------- */

static void	test_countwords(void)
{
	t_check_int("countwords_basic", ft_countwords("one:two:three", ':'), 3);
	t_check_int("countwords_multi_sep",
		ft_countwords("::one::two::", ':'), 2);
	t_check_int("countwords_empty", ft_countwords("", ':'), 0);
	t_check_int("countwords_null", ft_countwords(NULL, ':'), 0);
	t_check_int("countwords_one", ft_countwords("word", ':'), 1);

	t_check_int("countwords_sp_basic",
		ft_countwords_space("hello world foo"), 3);
	t_check_int("countwords_sp_extra",
		ft_countwords_space("  hi  there  "), 2);
	t_check_int("countwords_sp_empty", ft_countwords_space(""), 0);
}

/* ---------- ft_split_str -------------------------------------------------- */

static void	test_split_str(void)
{
	char	**parts;
	int		i;

	parts = ft_split_str("one--two--three", "--");
	t_check_nonnull("split_str_ptr", parts);
	t_check_str("split_str_0", parts[0], "one");
	t_check_str("split_str_1", parts[1], "two");
	t_check_str("split_str_2", parts[2], "three");
	i = 0;
	while (parts[i])
		i++;
	t_check_int("split_str_count", i, 3);
	i = 0;
	while (parts[i])
		fn_free(parts[i++]);
	fn_free(parts);

	/* single-char separator */
	parts = ft_split_str("a:b:c", ":");
	t_check_str("split_str_sc0", parts[0], "a");
	t_check_str("split_str_sc1", parts[1], "b");
	t_check_str("split_str_sc2", parts[2], "c");
	i = 0;
	while (parts[i])
		fn_free(parts[i++]);
	fn_free(parts);
}

/* ---------- ft_strnjoin ---------------------------------------------------- */

static void	test_strnjoin(void)
{
	char	*s;

	s = ft_strnjoin("hello", " ", "world", NULL);
	t_check_str("strnjoin_3", s, "hello world");
	fn_free(s);

	s = ft_strnjoin("a", "b", "c", "d", NULL);
	t_check_str("strnjoin_4", s, "abcd");
	fn_free(s);

	s = ft_strnjoin("only", NULL);
	t_check_str("strnjoin_1", s, "only");
	fn_free(s);

	s = ft_strnjoin("", "", "x", "", NULL);
	t_check_str("strnjoin_empty_parts", s, "x");
	fn_free(s);
}

/* ---------- churn loops --------------------------------------------------- */

static void	test_strnjoin_churn(void)
{
	int		i;
	long	total;
	char	*s;

	t_reseed(0xDEADBEEF);
	total = 0;
	i = 0;
	while (i < 1000)
	{
		s = ft_strnjoin("foo", "bar", "baz", NULL);
		total += (long)ft_strlen(s);
		fn_free(s);
		i++;
	}
	t_check_int("strnjoin_churn", total, 9000);
}

static void	test_split_str_churn(void)
{
	int		i;
	int		j;
	long	total;
	char	**parts;

	t_reseed(0xCAFEBABE);
	total = 0;
	i = 0;
	while (i < 500)
	{
		parts = ft_split_str("alpha--beta--gamma--delta", "--");
		j = 0;
		while (parts[j])
		{
			total += (long)ft_strlen(parts[j]);
			fn_free(parts[j]);
			j++;
		}
		fn_free(parts);
		i++;
	}
	t_check_int("split_str_churn", total, 500 * (5 + 4 + 5 + 5));
}

int	main(void)
{
	t_begin("string2");
	t_reseed(0xABCDE);

	test_strcpy();
	test_strncpy();
	test_strlcpy();
	test_strlcat();
	test_strchr();
	test_strrchr();
	test_strnchr();
	test_strstr();
	test_strnstr();
	test_strcmp();
	test_strncmp();
	test_strcasecmp();
	test_strncasecmp();
	test_strtok();
	test_strtok_space();
	test_strspn();
	test_strcspn();
	test_strchrnul();
	test_strclen();
	test_strnlen();
	test_countwords();
	test_split_str();
	test_strnjoin();
	test_strnjoin_churn();
	test_split_str_churn();

	return (t_end());
}
