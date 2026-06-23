/* ************************************************************************** */
/*   test_string.c — hammers the allocating string API; frees everything.     */
/*   Output is logical-only so the libc build and ft_malloc build must match.  */
/* ************************************************************************** */

#include "libft_test.h"

static char	up(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static void	bump(unsigned int i, char *c)
{
	*c = (char)(*c + (char)(i & 1));
}

static void	test_dup_substr_join(void)
{
	char	*a;
	char	*b;
	char	*c;

	a = ft_strdup("the quick brown fox jumps over the lazy dog");
	t_check_int("strdup_len", (long)ft_strlen(a), 43);
	b = ft_substr(a, 4, 5);
	t_check_str("substr", b, "quick");
	c = ft_strjoin(b, "!!");
	t_check_str("join", c, "quick!!");
	fn_free(c);
	c = ft_strndup(a, 9);
	t_check_str("strndup", c, "the quick");
	fn_free(c);
	fn_free(b);
	fn_free(a);
}

static void	test_trim_map_iter(void)
{
	char	*a;
	char	*b;

	a = ft_strtrim("\t  padded string  \n", " \t\n");
	t_check_str("trim", a, "padded string");
	b = ft_strmapi(a, up);
	t_check_str("mapi_upper", b, "PADDED STRING");
	ft_striteri(b, bump);
	t_check_int("iteri_len", (long)ft_strlen(b), 13);
	fn_free(b);
	fn_free(a);
}

static void	test_split(void)
{
	char	**parts;
	int		i;

	parts = ft_split("::a::bb:::ccc::", ':');
	t_check_nonnull("split_ptr", parts);
	t_check_str("split0", parts[0], "a");
	t_check_str("split1", parts[1], "bb");
	t_check_str("split2", parts[2], "ccc");
	i = 0;
	while (parts[i])
		i++;
	t_check_int("split_count", i, 3);
	i = 0;
	while (parts[i])
		fn_free(parts[i++]);
	fn_free(parts);
}

/* stress: 2000 strdup/substr/join cycles, all freed; proves no slow leak */
static void	test_churn(void)
{
	char	*s;
	char	*t;
	int		i;
	long	total;

	total = 0;
	i = 0;
	while (i < 2000)
	{
		s = ft_strdup("0123456789abcdefghijklmnopqrstuvwxyz");
		t = ft_substr(s, (unsigned int)(t_rand() % 30), 6);
		total += (long)ft_strlen(t);
		fn_free(t);
		fn_free(s);
		i++;
	}
	t_check_int("churn_total", total, 12000);
}

int	main(void)
{
	t_begin("string");
	t_reseed(0xC0FFEE);
	test_dup_substr_join();
	test_trim_map_iter();
	test_split();
	test_churn();
	return (t_end());
}
