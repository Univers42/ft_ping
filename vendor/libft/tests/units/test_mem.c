/* ************************************************************************** */
/*   test_mem.c — tests for ft_memory.h functions:                           */
/*   ft_memcpy, ft_memmove (overlaps), ft_memset, ft_bzero, ft_memchr,       */
/*   ft_memcmp, ft_memccpy, and xfn_malloc/xfn_calloc/xfn_realloc/xfn_free  */
/* ************************************************************************** */

#include "libft_test.h"
#include "ft_memory.h"
#include <string.h>
#include <limits.h>

/* ---- ft_memset ---- */
static void	test_memset(void)
{
	unsigned char	buf[64];
	unsigned char	ref[64];

	memset(ref, 0xAB, 64);
	ft_memset(buf, 0xAB, 64);
	t_check_mem("memset_fill_ab", buf, ref, 64);

	memset(ref, 0, 64);
	ft_memset(buf, 0, 64);
	t_check_mem("memset_fill_zero", buf, ref, 64);

	memset(ref, 0xFF, 1);
	ft_memset(buf, 0xFF, 1);
	t_check_mem("memset_one_byte", buf, ref, 1);

	/* n=0: must be a no-op */
	memset(buf, 0x55, 8);
	ft_memset(buf, 0xAA, 0);
	memset(ref, 0x55, 8);
	t_check_mem("memset_zero_n", buf, ref, 8);

	/* value is int; only low 8 bits used */
	ft_memset(buf, 0x1FF, 4);
	memset(ref, 0xFF, 4);
	t_check_mem("memset_value_mask", buf, ref, 4);
}

/* ---- ft_bzero ---- */
static void	test_bzero(void)
{
	unsigned char	buf[32];
	unsigned char	ref[32];

	ft_memset(buf, 0xCC, 32);
	ft_bzero(buf, 32);
	memset(ref, 0, 32);
	t_check_mem("bzero_full", buf, ref, 32);

	ft_memset(buf, 0xCC, 32);
	ft_bzero(buf, 0);
	memset(ref, 0xCC, 32);
	t_check_mem("bzero_zero_n", buf, ref, 32);

	ft_memset(buf, 0xDD, 32);
	ft_bzero(buf, 1);
	t_check_int("bzero_one_byte", (long)buf[0], 0);
	t_check_int("bzero_one_byte_next", (long)buf[1], 0xDD);
}

/* ---- ft_memcpy ---- */
static void	test_memcpy(void)
{
	char		src[64];
	char		dst[64];
	char		ref[64];
	void		*ret;

	ft_memset(src, 0, 64);
	ft_memset(dst, 0, 64);
	ft_memset(ref, 0, 64);

	memcpy(src, "Hello, world!", 14);
	memcpy(ref, "Hello, world!", 14);

	ret = ft_memcpy(dst, src, 14);
	t_check_mem("memcpy_hello", dst, ref, 14);
	t_check("memcpy_ret_is_dst", ret == (void *)dst);

	/* copy 1 byte */
	ft_memset(dst, 0, 64);
	ft_memcpy(dst, src, 1);
	t_check_int("memcpy_one_byte", (long)(unsigned char)dst[0], (long)'H');

	/* copy 0 bytes: dst untouched, returns dst */
	ft_memset(dst, 0x77, 4);
	ret = ft_memcpy(dst, src, 0);
	t_check("memcpy_zero_n_ret", ret == (void *)dst);
	t_check_int("memcpy_zero_n_untouched", (long)(unsigned char)dst[0], 0x77);

	/* large copy via xfn_malloc buffers */
	{
		size_t	sz = 4096;
		unsigned char	*big_src = xfn_malloc(sz);
		unsigned char	*big_dst = xfn_malloc(sz);
		unsigned int	i;

		i = 0;
		while (i < sz)
		{
			big_src[i] = (unsigned char)(i & 0xFF);
			i++;
		}
		ft_memcpy(big_dst, big_src, sz);
		t_check_mem("memcpy_4096", big_dst, big_src, sz);
		xfn_free(big_src);
		xfn_free(big_dst);
	}
}

/* ---- ft_memmove (including overlapping) ---- */
static void	test_memmove(void)
{
	char	buf[128];
	char	ref[128];
	void	*ret;

	/* non-overlapping forward */
	ft_memset(buf, 0, 128);
	memcpy(buf, "abcdefghij", 10);
	memcpy(ref, "abcdefghij", 10);
	memmove(ref + 20, ref, 10);
	ret = ft_memmove(buf + 20, buf, 10);
	t_check_mem("memmove_noovlp", buf + 20, ref + 20, 10);
	t_check("memmove_ret", ret == (void *)(buf + 20));

	/* overlap: dst > src (copy backwards needed) */
	ft_memset(buf, 0, 128);
	memcpy(buf, "0123456789", 10);
	memmove(buf + 4, buf, 10);
	ft_memset(ref, 0, 128);
	memcpy(ref, "0123012345", 10);
	/* libc result: "01230123456789" starting at 0 */
	{
		char	lbuf[128];
		char	lref[128];

		memset(lbuf, 0, 128);
		memset(lref, 0, 128);
		memcpy(lbuf, "0123456789", 10);
		memcpy(lref, "0123456789", 10);
		memmove(lref + 4, lref, 10);
		ft_memmove(lbuf + 4, lbuf, 10);
		t_check_mem("memmove_dst_gt_src", lbuf, lref, 14);
	}

	/* overlap: src > dst (forward copy ok) */
	{
		char	lbuf[128];
		char	lref[128];

		memset(lbuf, 0, 128);
		memset(lref, 0, 128);
		memcpy(lbuf, "xxxx0123456789", 14);
		memcpy(lref, "xxxx0123456789", 14);
		memmove(lref, lref + 4, 10);
		ft_memmove(lbuf, lbuf + 4, 10);
		t_check_mem("memmove_src_gt_dst", lbuf, lref, 14);
	}

	/* copy 0 bytes */
	{
		char	lbuf[8] = "ABCDEFG";
		char	lref[8] = "ABCDEFG";
		void	*r;

		r = ft_memmove(lbuf, lbuf + 2, 0);
		t_check("memmove_zero_n_ret", r == (void *)lbuf);
		t_check_mem("memmove_zero_n_unchanged", lbuf, lref, 7);
	}

	/* full overlap (src == dst) */
	{
		char	lbuf[8] = "ABCDEFG";
		char	lref[8] = "ABCDEFG";

		ft_memmove(lbuf, lbuf, 7);
		t_check_mem("memmove_same", lbuf, lref, 7);
	}
}

/* ---- ft_memchr ---- */
static void	test_memchr(void)
{
	const char	*haystack = "the quick brown fox";
	void		*got;
	void		*exp;

	got = ft_memchr(haystack, 'q', 20);
	exp = memchr(haystack, 'q', 20);
	t_check("memchr_found_q", got == exp);

	got = ft_memchr(haystack, 'z', 20);
	exp = memchr(haystack, 'z', 20);
	t_check("memchr_notfound", got == NULL && exp == NULL);

	/* stop before end */
	got = ft_memchr(haystack, 'o', 8);
	exp = memchr(haystack, 'o', 8);
	t_check("memchr_limited_n", got == exp);

	/* search for embedded NUL: not relevant, but 0-byte in window */
	{
		char	data[8] = {'a', 'b', '\0', 'c', 'd', 'e', 'f', 'g'};

		got = ft_memchr(data, '\0', 8);
		exp = memchr(data, '\0', 8);
		t_check("memchr_nul_byte", got == exp);
	}

	/* n=0: must return NULL */
	got = ft_memchr(haystack, 't', 0);
	t_check("memchr_zero_n", got == NULL);

	/* value as int > 255 — only low byte matters */
	got = ft_memchr(haystack, 't' + 256, 20);
	exp = memchr(haystack, 't' + 256, 20);
	t_check("memchr_value_mask", got == exp);
}

/* ---- ft_memcmp ---- */
static void	test_memcmp(void)
{
	const char	*a = "abcdef";
	const char	*b = "abcXef";
	int			got;
	int			exp;

	/* equal */
	got = ft_memcmp(a, a, 6);
	t_check("memcmp_equal", got == 0);

	/* differ at position 3 */
	got = ft_memcmp(a, b, 6);
	exp = memcmp(a, b, 6);
	t_check("memcmp_differ_sign", (got < 0) == (exp < 0));

	/* compare only 3 bytes: same */
	got = ft_memcmp(a, b, 3);
	t_check("memcmp_prefix_eq", got == 0);

	/* n=0: always 0 */
	got = ft_memcmp("X", "Y", 0);
	t_check("memcmp_zero_n", got == 0);

	/* byte 0x80 > 0x7F (unsigned comparison) */
	{
		unsigned char	hi[1] = {0x80};
		unsigned char	lo[1] = {0x7F};

		got = ft_memcmp(hi, lo, 1);
		exp = memcmp(hi, lo, 1);
		t_check("memcmp_unsigned", (got > 0) == (exp > 0));
	}
}

/* ---- ft_memccpy ---- */
static void	test_memccpy(void)
{
	char	dst[64];
	char	ref[64];
	void	*got;
	void	*exp;

	ft_memset(dst, 0, 64);
	ft_memset(ref, 0, 64);

	/* delimiter found */
	got = ft_memccpy(dst, "hello world", ' ', 12);
	exp = memccpy(ref, "hello world", ' ', 12);
	/* returned pointer should point one byte past the delimiter */
	t_check("memccpy_ret_nonnull", got != NULL);
	t_check("memccpy_ret_eq", (char *)got - dst == (char *)exp - ref);
	t_check_mem("memccpy_content", dst, ref, 6);

	/* delimiter not found: copies n bytes, returns NULL */
	ft_memset(dst, 0, 64);
	ft_memset(ref, 0, 64);
	got = ft_memccpy(dst, "abcdef", 'z', 6);
	exp = memccpy(ref, "abcdef", 'z', 6);
	t_check("memccpy_notfound_null", got == NULL && exp == NULL);
	t_check_mem("memccpy_notfound_content", dst, ref, 6);

	/* n=0 */
	ft_memset(dst, 0xBB, 4);
	got = ft_memccpy(dst, "abcd", 'a', 0);
	t_check("memccpy_zero_n", got == NULL);
}

/* ---- xfn_malloc / xfn_calloc / xfn_realloc / xfn_free churn ---- */
static void	test_xfn_wrappers(void)
{
	/* basic alloc/free */
	{
		char	*p = xfn_malloc(32);

		t_check_nonnull("xfn_malloc_basic", p);
		ft_memset(p, 0xAA, 32);
		xfn_free(p);
	}

	/* xfn_calloc: zero-initialised */
	{
		unsigned char	*p = xfn_calloc(64, 1);
		unsigned int	i;
		int				all_zero;

		t_check_nonnull("xfn_calloc_nonnull", p);
		all_zero = 1;
		i = 0;
		while (i < 64)
		{
			if (p[i] != 0)
				all_zero = 0;
			i++;
		}
		t_check("xfn_calloc_zeroed", all_zero);
		xfn_free(p);
	}

	/* xfn_realloc: grow */
	{
		char	*p = xfn_malloc(16);
		char	*p2;

		ft_memset(p, 0x55, 16);
		p2 = xfn_realloc(p, 16, 64);
		t_check_nonnull("xfn_realloc_nonnull", p2);
		{
			char	ref[16];
			ft_memset(ref, 0x55, 16);
			t_check_mem("xfn_realloc_preserved", p2, ref, 16);
		}
		xfn_free(p2);
	}

	/* xfn_realloc: shrink */
	{
		char	*p = xfn_malloc(128);
		char	*p2;

		ft_memset(p, 0x33, 128);
		p2 = xfn_realloc(p, 128, 8);
		t_check_nonnull("xfn_realloc_shrink_nonnull", p2);
		{
			char	ref[8];
			ft_memset(ref, 0x33, 8);
			t_check_mem("xfn_realloc_shrink_prefix", p2, ref, 8);
		}
		xfn_free(p2);
	}

	/* xfn_realloc: to zero => returns NULL, frees old */
	{
		char	*p = xfn_malloc(16);
		char	*p2;

		ft_memset(p, 0x11, 16);
		p2 = xfn_realloc(p, 16, 0);
		t_check("xfn_realloc_zero_null", p2 == NULL);
		/* p is already freed by xfn_realloc — do not free again */
	}

	/* xfn_free: NULL is safe */
	xfn_free(NULL);
	t_check("xfn_free_null_safe", 1);
}

/* ---- Allocation churn: many sizes, patterns verified ---- */
#define CHURN_SLOTS 64
#define CHURN_ITER  1200

static void	test_alloc_churn(void)
{
	void		*slots[CHURN_SLOTS];
	size_t		sizes[CHURN_SLOTS];
	unsigned int	i;
	unsigned int	idx;
	unsigned int	op;
	long		patterns_ok;
	long		patterns_checked;

	t_reseed(0xDEADBEEF);
	ft_memset(slots, 0, sizeof(slots));
	ft_memset(sizes, 0, sizeof(sizes));
	patterns_ok = 0;
	patterns_checked = 0;

	i = 0;
	while (i < CHURN_ITER)
	{
		idx = t_rand() % CHURN_SLOTS;
		op = t_rand() % 3;

		if (op == 0 || slots[idx] == NULL)
		{
			/* allocate */
			if (slots[idx])
				xfn_free(slots[idx]);
			sizes[idx] = (t_rand() % 511) + 1;
			slots[idx] = xfn_malloc(sizes[idx]);
			if (slots[idx])
				ft_memset(slots[idx], (int)(idx & 0xFF), sizes[idx]);
		}
		else if (op == 1)
		{
			/* realloc */
			size_t	newsize = (t_rand() % 1023) + 1;
			void	*p2 = xfn_realloc(slots[idx], sizes[idx], newsize);
			if (p2)
			{
				slots[idx] = p2;
				sizes[idx] = newsize;
				ft_memset(slots[idx], (int)(idx & 0xFF), sizes[idx]);
			}
		}
		else
		{
			/* verify pattern then free */
			unsigned char	*p = (unsigned char *)slots[idx];
			unsigned char	expected = (unsigned char)(idx & 0xFF);
			size_t			j;
			int				ok = 1;

			j = 0;
			while (j < sizes[idx])
			{
				if (p[j] != expected)
				{
					ok = 0;
					break ;
				}
				j++;
			}
			patterns_ok += ok;
			patterns_checked++;
			xfn_free(slots[idx]);
			slots[idx] = NULL;
			sizes[idx] = 0;
		}
		i++;
	}

	/* free remaining */
	i = 0;
	while (i < CHURN_SLOTS)
	{
		if (slots[i])
			xfn_free(slots[i]);
		i++;
	}

	t_check("churn_patterns_ok", patterns_ok == patterns_checked);
	t_check_int("churn_checked_nonzero", patterns_checked > 0, 1);
}

int	main(void)
{
	t_begin("mem");
	t_reseed(0xBEEF1234);
	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_memchr();
	test_memcmp();
	test_memccpy();
	test_xfn_wrappers();
	test_alloc_churn();
	return (t_end());
}
