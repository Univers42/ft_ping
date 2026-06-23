/* ************************************************************************** */
/*   test_std.c — tests for ft_stdlib.h functions:                           */
/*   ft_atoi, ft_atoi_base, ft_itoa, ft_utoa, ft_xtoa, ft_calloc,           */
/*   fn_realloc3                                                              */
/* ************************************************************************** */

#include "libft_test.h"
#include "ft_stdlib.h"
#include <limits.h>
#include <string.h>

/* ---- ft_atoi ---- */
static void	test_atoi(void)
{
	t_check_int("atoi_zero",        (long)ft_atoi("0"),          0L);
	t_check_int("atoi_pos",         (long)ft_atoi("42"),         42L);
	t_check_int("atoi_neg",         (long)ft_atoi("-42"),        -42L);
	t_check_int("atoi_plus",        (long)ft_atoi("+42"),        42L);
	t_check_int("atoi_spaces",      (long)ft_atoi("   7"),       7L);
	t_check_int("atoi_tab_space",   (long)ft_atoi("\t  \n-99"), -99L);
	t_check_int("atoi_intmax",      (long)ft_atoi("2147483647"), (long)INT_MAX);
	t_check_int("atoi_intmin",      (long)ft_atoi("-2147483648"), (long)INT_MIN);
	t_check_int("atoi_trailing",    (long)ft_atoi("123abc"),     123L);
	t_check_int("atoi_empty",       (long)ft_atoi(""),           0L);
	t_check_int("atoi_nondigt",     (long)ft_atoi("abc"),        0L);
	t_check_int("atoi_double_neg",  (long)ft_atoi("--5"),        0L);
}

/* ---- ft_atoi_base ---- */
static void	test_atoi_base(void)
{
	t_check_int("atoi_base2",    (long)ft_atoi_base("101010", 2),    42L);
	t_check_int("atoi_base16_lo", (long)ft_atoi_base("2a", 16),     42L);
	t_check_int("atoi_base16_hi", (long)ft_atoi_base("2A", 16),     42L);
	t_check_int("atoi_base8",    (long)ft_atoi_base("52", 8),        42L);
	t_check_int("atoi_base10",   (long)ft_atoi_base("42", 10),       42L);
	t_check_int("atoi_base36",   (long)ft_atoi_base("Z", 36),        35L);
	t_check_int("atoi_base_neg", (long)ft_atoi_base("-101010", 2),  -42L);
	t_check_int("atoi_base_spc", (long)ft_atoi_base("  +42", 10),   42L);
	t_check_int("atoi_base_dbl_sign", (long)ft_atoi_base("--5", 10), 0L);
	t_check_int("atoi_base_zero", (long)ft_atoi_base("0", 10),       0L);
	t_check_int("atoi_base_hex_ff", (long)ft_atoi_base("FF", 16),  255L);
}

/* ---- ft_itoa ---- */
static void	test_itoa(void)
{
	char	*s;

	s = ft_itoa(0);
	t_check_str("itoa_zero", s, "0");
	fn_free(s);

	s = ft_itoa(42);
	t_check_str("itoa_pos", s, "42");
	fn_free(s);

	s = ft_itoa(-42);
	t_check_str("itoa_neg", s, "-42");
	fn_free(s);

	s = ft_itoa(INT_MAX);
	t_check_str("itoa_intmax", s, "2147483647");
	fn_free(s);

	s = ft_itoa(INT_MIN);
	t_check_str("itoa_intmin", s, "-2147483648");
	fn_free(s);

	s = ft_itoa(1);
	t_check_str("itoa_one", s, "1");
	fn_free(s);

	s = ft_itoa(-1);
	t_check_str("itoa_neg_one", s, "-1");
	fn_free(s);

	s = ft_itoa(1000000000);
	t_check_str("itoa_billion", s, "1000000000");
	fn_free(s);
}

/* ---- ft_utoa ---- */
static void	test_utoa(void)
{
	char	*s;

	s = ft_utoa(0);
	t_check_str("utoa_zero", s, "0");
	fn_free(s);

	s = ft_utoa(42);
	t_check_str("utoa_42", s, "42");
	fn_free(s);

	s = ft_utoa((unsigned int)INT_MAX);
	t_check_str("utoa_intmax", s, "2147483647");
	fn_free(s);

	s = ft_utoa(UINT_MAX);
	t_check_str("utoa_uintmax", s, "4294967295");
	fn_free(s);

	s = ft_utoa(1);
	t_check_str("utoa_one", s, "1");
	fn_free(s);
}

/* ---- ft_xtoa ---- */
static void	test_xtoa(void)
{
	char	*s;

	s = ft_xtoa(0, 0);
	t_check_str("xtoa_zero_lower", s, "0");
	fn_free(s);

	s = ft_xtoa(255, 0);
	t_check_str("xtoa_ff_lower", s, "ff");
	fn_free(s);

	s = ft_xtoa(255, 1);
	t_check_str("xtoa_ff_upper", s, "FF");
	fn_free(s);

	s = ft_xtoa(0xDEADBEEF, 1);
	t_check_str("xtoa_deadbeef", s, "DEADBEEF");
	fn_free(s);

	s = ft_xtoa(0xDEADBEEF, 0);
	t_check_str("xtoa_deadbeef_lo", s, "deadbeef");
	fn_free(s);

	s = ft_xtoa(16, 0);
	t_check_str("xtoa_16", s, "10");
	fn_free(s);

	/* 0x2a == 42 */
	s = ft_xtoa(42, 0);
	t_check_str("xtoa_42", s, "2a");
	fn_free(s);
}

/* ---- ft_calloc ---- */
static void	test_calloc(void)
{
	/* basic zero-init */
	{
		unsigned char	*p = ft_calloc(16, 1);
		unsigned int	i;
		int				all_zero;

		t_check_nonnull("calloc_nonnull", p);
		all_zero = 1;
		i = 0;
		while (i < 16)
		{
			if (p[i] != 0)
				all_zero = 0;
			i++;
		}
		t_check("calloc_zeroed", all_zero);
		fn_free(p);
	}

	/* nmemb=0: either NULL or freeable non-NULL (we accept non-NULL) */
	{
		void	*p = ft_calloc(0, 4);

		/* just free whatever was returned (fn_free(NULL) is safe) */
		fn_free(p);
		t_check("calloc_zero_nmemb_ok", 1);
	}

	/* size=1, many elements */
	{
		unsigned char	*p = ft_calloc(256, 1);
		unsigned int	i;
		int				all_zero;

		t_check_nonnull("calloc_256", p);
		all_zero = 1;
		i = 0;
		while (i < 256)
		{
			if (p[i] != 0)
				all_zero = 0;
			i++;
		}
		t_check("calloc_256_zeroed", all_zero);
		fn_free(p);
	}

	/* word-sized element */
	{
		int	*p = ft_calloc(8, sizeof(int));
		int	all_zero;
		int	j;

		t_check_nonnull("calloc_ints", p);
		all_zero = 1;
		j = 0;
		while (j < 8)
		{
			if (p[j] != 0)
				all_zero = 0;
			j++;
		}
		t_check("calloc_ints_zeroed", all_zero);
		fn_free(p);
	}
}

/* ---- fn_realloc3 (3-arg) ---- */
static void	test_fn_realloc3(void)
{
	/* grow: prefix preserved */
	{
		char	*p = fn_malloc(16);
		char	*p2;
		char	ref[16];

		ft_memset(p, 0x77, 16);
		ft_memset(ref, 0x77, 16);
		p2 = fn_realloc3(p, 16, 64);
		t_check_nonnull("realloc3_grow_nonnull", p2);
		t_check_mem("realloc3_grow_prefix", p2, ref, 16);
		fn_free(p2);
	}

	/* shrink: first new_cap bytes preserved */
	{
		char	*p = fn_malloc(64);
		char	*p2;
		char	ref[8];

		ft_memset(p, 0x55, 64);
		ft_memset(ref, 0x55, 8);
		p2 = fn_realloc3(p, 64, 8);
		t_check_nonnull("realloc3_shrink_nonnull", p2);
		t_check_mem("realloc3_shrink_prefix", p2, ref, 8);
		fn_free(p2);
	}

	/* new_cap = 0: returns NULL */
	{
		char	*p = fn_malloc(16);
		char	*p2;

		ft_memset(p, 0x11, 16);
		p2 = fn_realloc3(p, 16, 0);
		t_check("realloc3_zero_null", p2 == NULL);
		/* p is freed by fn_realloc3 when new_cap==0 */
	}

	/* ptr = NULL: acts like malloc */
	{
		char	*p2 = fn_realloc3(NULL, 0, 32);

		t_check_nonnull("realloc3_null_ptr", p2);
		fn_free(p2);
	}

	/* churn: repeatedly grow a string buffer */
	{
		char	*buf = NULL;
		size_t	cap = 0;
		size_t	newcap;
		int		i;
		long	total_len;

		total_len = 0;
		i = 0;
		while (i < 64)
		{
			newcap = cap + 16;
			buf = fn_realloc3(buf, cap, newcap);
			t_check_nonnull("realloc3_churn_nonnull", buf);
			if (!buf)
				break ;
			ft_memset(buf + cap, 'A' + (i % 26), 16);
			cap = newcap;
			total_len += 16;
			i++;
		}
		if (buf)
		{
			t_check_int("realloc3_churn_total", total_len, 64 * 16L);
			fn_free(buf);
		}
	}
}

/* ---- Round-trip: itoa -> atoi ---- */
static void	test_roundtrip(void)
{
	int		vals[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN,
		100, -100, 999, -999, 12345, -12345};
	int		n_vals = 13;
	int		i;

	i = 0;
	while (i < n_vals)
	{
		char	*s = ft_itoa(vals[i]);
		long	back = ft_atoi(s);

		t_check_int("roundtrip", back, (long)vals[i]);
		fn_free(s);
		i++;
	}
}

int	main(void)
{
	t_begin("std");
	t_reseed(0xC0DE4242);
	test_atoi();
	test_atoi_base();
	test_itoa();
	test_utoa();
	test_xtoa();
	test_calloc();
	test_fn_realloc3();
	test_roundtrip();
	return (t_end());
}
