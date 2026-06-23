/* ************************************************************************** */
/*   bench_libft.c — allocation-bound workloads, timed. Compiled twice         */
/*   (libc vs ft_malloc) by tests/bench.sh; prints per-scenario nanoseconds.   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

static unsigned long long	g_rng = 0x9e3779b97f4a7c15ULL;

static unsigned int	xr(void)
{
	g_rng = g_rng * 6364136223846793005ULL + 1442695040888963407ULL;
	return ((unsigned int)(g_rng >> 33));
}

static double	now_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1e6);
}

/* small-block churn: the workload that distinguishes allocators */
static void	bench_small_churn(long iters)
{
	void	*slots[256];
	long	i;
	int		k;

	memset(slots, 0, sizeof(slots));
	i = 0;
	while (i < iters)
	{
		k = (int)(xr() & 255);
		if (slots[k])
			fn_free(slots[k]);
		slots[k] = fn_malloc(8 + (xr() & 511));
		i++;
	}
	k = -1;
	while (++k < 256)
		if (slots[k])
			fn_free(slots[k]);
}

/* realloc growth: repeatedly grow a buffer */
static void	bench_realloc(long iters)
{
	long	i;
	size_t	cap;
	char	*p;

	i = 0;
	while (i < iters)
	{
		cap = 8;
		p = fn_malloc(cap);
		while (cap < 8192)
		{
			cap *= 2;
			p = fn_realloc(p, cap);
		}
		fn_free(p);
		i++;
	}
}

/* real-libft workload: split + join + dup, all freed */
static void	bench_string(long iters)
{
	long	i;
	char	**parts;
	char	*j;
	int		k;

	i = 0;
	while (i < iters)
	{
		parts = ft_split("alpha,beta,gamma,delta,epsilon,zeta,eta", ',');
		j = ft_strjoin(parts[0], parts[6]);
		fn_free(j);
		k = -1;
		while (parts[++k])
			fn_free(parts[k]);
		fn_free(parts);
		i++;
	}
}

static void	run(const char *label, void (*fn)(long), long iters)
{
	double	t0;
	double	t1;

	t0 = now_ms();
	fn(iters);
	t1 = now_ms();
	printf("%-16s %10.2f ms  (%ld iters)\n", label, t1 - t0, iters);
}

int	main(void)
{
#ifdef HAVE_FT_MALLOC
	printf("# allocator: ft_malloc\n");
#else
	printf("# allocator: libc\n");
#endif
	run("small_churn", bench_small_churn, 2000000);
	run("realloc_grow", bench_realloc, 200000);
	run("split_join", bench_string, 200000);
	return (0);
}
