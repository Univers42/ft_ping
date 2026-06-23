/* ************************************************************************** */
/*                                                                            */
/*   libft_test.h — test harness for libft (libc vs ft_malloc comparison)     */
/*                                                                            */
/*   Design contract:                                                         */
/*     * STDOUT  = deterministic LOGICAL results only (no pointers, no times) */
/*                 -> the orchestrator diffs stdout of the libc build against  */
/*                    the ft_malloc build; they MUST be byte-identical.        */
/*     * STDERR  = diagnostics + leak report (per-allocator, never diffed).    */
/*     * exit()  = 0 iff every check passed AND (ft build) 0 bytes still live. */
/*                                                                            */
/*   Each test is a standalone program: #include this, write checks, return   */
/*   t_end(). Use t_check_* so a wrong libft fails the exit code in BOTH       */
/*   builds, while the cross-build stdout diff catches allocator corruption.   */
/* ************************************************************************** */

#ifndef LIBFT_TEST_H
# define LIBFT_TEST_H

# include "libft.h"
# include <stdio.h>
# include <string.h>

# ifdef HAVE_FT_MALLOC
size_t	malloc_live_bytes(void);
size_t	malloc_live_count(void);
# endif

static int	g_t_checks = 0;
static int	g_t_fail = 0;
static const char	*g_t_name = "test";

/* Deterministic 64-bit LCG so "randomised" tests are reproducible & identical. */
static unsigned long long	g_t_rng = 0x9e3779b97f4a7c15ULL;

static inline unsigned int	t_rand(void)
{
	g_t_rng = g_t_rng * 6364136223846793005ULL + 1442695040888963407ULL;
	return ((unsigned int)(g_t_rng >> 33));
}

static inline void	t_reseed(unsigned long long seed)
{
	g_t_rng = seed ? seed : 0x9e3779b97f4a7c15ULL;
}

static inline void	t_begin(const char *name)
{
	g_t_name = name;
	printf("== %s ==\n", name);
}

/* boolean assertion */
static inline int	t_check(const char *label, int cond)
{
	g_t_checks++;
	if (cond)
		printf("%s: PASS\n", label);
	else
	{
		printf("%s: FAIL\n", label);
		g_t_fail++;
	}
	return (cond);
}

/* integer equality (prints the value so the diff also compares the result) */
static inline int	t_check_int(const char *label, long got, long exp)
{
	g_t_checks++;
	if (got == exp)
		printf("%s = %ld: PASS\n", label, got);
	else
	{
		printf("%s = %ld (exp %ld): FAIL\n", label, got, exp);
		g_t_fail++;
	}
	return (got == exp);
}

/* string equality (NULL-safe; prints the value) */
static inline int	t_check_str(const char *label, const char *got, const char *exp)
{
	int	ok;

	g_t_checks++;
	if (!got || !exp)
		ok = (got == exp);
	else
		ok = (strcmp(got, exp) == 0);
	if (ok)
		printf("%s = \"%s\": PASS\n", label, got ? got : "(null)");
	else
	{
		printf("%s = \"%s\" (exp \"%s\"): FAIL\n",
			label, got ? got : "(null)", exp ? exp : "(null)");
		g_t_fail++;
	}
	return (ok);
}

/* raw-memory equality over n bytes */
static inline int	t_check_mem(const char *label, const void *got,
		const void *exp, size_t n)
{
	int	ok;

	g_t_checks++;
	ok = (got && exp && memcmp(got, exp, n) == 0);
	printf("%s[%zu]: %s\n", label, n, ok ? "PASS" : "FAIL");
	if (!ok)
		g_t_fail++;
	return (ok);
}

/* pointer non-NULL assertion (does not print the pointer) */
static inline int	t_check_nonnull(const char *label, const void *p)
{
	return (t_check(label, p != NULL));
}

static inline int	t_end(void)
{
	int	rc;

	rc = (g_t_fail != 0);
	fprintf(stderr, "[%s] %d checks, %d failed\n",
		g_t_name, g_t_checks, g_t_fail);
# ifdef HAVE_FT_MALLOC
	{
		size_t	live;

		live = malloc_live_bytes();
		fprintf(stderr, "[%s] ft_malloc live: %zu bytes / %zu blocks\n",
			g_t_name, live, malloc_live_count());
		if (live != 0)
		{
			fprintf(stderr, "[%s] LEAK: %zu bytes still live\n",
				g_t_name, live);
			rc = 1;
		}
	}
# endif
	return (rc);
}

#endif
