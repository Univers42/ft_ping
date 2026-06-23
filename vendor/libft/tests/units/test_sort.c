/* ************************************************************************** */
/*   test_sort.c — exercises every sort algorithm in libft.                  */
/*   Checks: (a) non-decreasing output, (b) same multiset as input.          */
/*   Output is logical-only so libc and ft_malloc builds produce same stdout. */
/* ************************************************************************** */

#include "libft_test.h"
#include "ft_sort.h"
#include <string.h>

/* ft_sort.h declares radi_sort but the compiled symbol is radix_sort;
   forward-declare the real one so we can call it without implicit-decl. */
void	radix_sort(int *arr, int size, int max_bits);

/* ---- utilities ---------------------------------------------------------- */

#define LARGE_N 10000
#define MED_N   512
#define SMALL_N 8

/* Allocate a fresh int array via fn_malloc and fill it deterministically. */
static int	*make_rand_arr(int n, unsigned long long seed)
{
	int	*arr;
	int	i;

	arr = fn_malloc((size_t)n * sizeof(int));
	if (!arr)
		return (NULL);
	t_reseed(seed);
	i = 0;
	while (i < n)
	{
		arr[i] = (int)(t_rand() & 0x7FFFFFFF);
		i++;
	}
	return (arr);
}

static int	*make_rand_small_arr(int n, unsigned long long seed)
{
	int	*arr;
	int	i;

	arr = fn_malloc((size_t)n * sizeof(int));
	if (!arr)
		return (NULL);
	t_reseed(seed);
	i = 0;
	while (i < n)
	{
		/* small range [0..1023] so counting/radix/pigeonhole are cheap */
		arr[i] = (int)(t_rand() % 1024);
		i++;
	}
	return (arr);
}

/* Non-decreasing check. */
static int	is_sorted(int *arr, int n)
{
	int	i;

	i = 1;
	while (i < n)
	{
		if (arr[i] < arr[i - 1])
			return (0);
		i++;
	}
	return (1);
}

/*
 * Permutation check via sum, XOR, and min/max.
 * Together they catch most reordering / duplication / loss bugs without
 * requiring an extra sort or hash table.
 */
static int	is_permutation(int *orig, int *sorted, int n)
{
	long long	sum_o;
	long long	sum_s;
	long long	xor_o;
	long long	xor_s;
	int			i;

	sum_o = 0;
	sum_s = 0;
	xor_o = 0;
	xor_s = 0;
	i = 0;
	while (i < n)
	{
		sum_o += orig[i];
		sum_s += sorted[i];
		xor_o ^= orig[i];
		xor_s ^= sorted[i];
		i++;
	}
	return (sum_o == sum_s && xor_o == xor_s);
}

/* Copy arr[0..n-1] into a new fn_malloc buffer. */
static int	*copy_arr(int *arr, int n)
{
	int	*cp;

	cp = fn_malloc((size_t)n * sizeof(int));
	if (!cp)
		return (NULL);
	memcpy(cp, arr, (size_t)n * sizeof(int));
	return (cp);
}

/* All-equal array. */
static int	*make_equal_arr(int n, int val)
{
	int	*arr;
	int	i;

	arr = fn_malloc((size_t)n * sizeof(int));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = val;
		i++;
	}
	return (arr);
}

/* Already-sorted (ascending) array. */
static int	*make_asc_arr(int n)
{
	int	*arr;
	int	i;

	arr = fn_malloc((size_t)n * sizeof(int));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = i;
		i++;
	}
	return (arr);
}

/* Reverse-sorted (descending) array. */
static int	*make_desc_arr(int n)
{
	int	*arr;
	int	i;

	arr = fn_malloc((size_t)n * sizeof(int));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = n - 1 - i;
		i++;
	}
	return (arr);
}

/* ---- generic test driver ------------------------------------------------ */

typedef void	(*t_sort_fn)(int *, int);

/*
 * Run sort_fn on arr[0..n-1], passing orig as the reference for the
 * permutation check.  Returns 1 if both invariants hold.
 * sort_fn signature: void fn(int *arr, int size)
 */
static int	verify_sort(t_sort_fn fn, int *arr, int *orig, int n)
{
	fn(arr, n);
	if (!is_sorted(arr, n))
		return (0);
	if (!is_permutation(orig, arr, n))
		return (0);
	return (1);
}

/* ---- edge-case helper: size-0 and size-1 must not crash ----------------- */

static void	edge_size0_size1(const char *name, t_sort_fn fn)
{
	int	*arr0;
	int	*arr1;
	int	one;

	arr0 = fn_malloc(0);	/* may return NULL or a tiny block; both fine */
	one = 42;
	arr1 = copy_arr(&one, 1);

	fn(arr0, 0);
	fn(arr1, 1);
	t_check("edge0_no_crash", 1);
	t_check("edge1_sorted", arr1[0] == 42);
	(void)name;
	fn_free(arr0);
	fn_free(arr1);
}

/* Macro: run a battery for a named sort (void(int*,int) signature). */
#define SORT_BATTERY(label, fn, seed) do { \
	int *_arr; int *_orig; int *_eq; int *_asc; int *_desc; int *_lg; int *_lgorig; \
	/* random medium */ \
	_arr  = make_rand_arr(MED_N, (seed)); \
	_orig = copy_arr(_arr, MED_N); \
	t_check((label "_med_sorted"), verify_sort((fn), _arr, _orig, MED_N)); \
	fn_free(_arr); fn_free(_orig); \
	/* all equal */ \
	_eq = make_equal_arr(MED_N, 7); \
	t_check((label "_equal"), verify_sort((fn), _eq, _eq, MED_N)); \
	fn_free(_eq); \
	/* already sorted */ \
	_asc = make_asc_arr(MED_N); \
	_orig = copy_arr(_asc, MED_N); \
	t_check((label "_asc"), verify_sort((fn), _asc, _orig, MED_N)); \
	fn_free(_asc); fn_free(_orig); \
	/* reverse sorted */ \
	_desc = make_desc_arr(MED_N); \
	_orig = copy_arr(_desc, MED_N); \
	t_check((label "_desc"), verify_sort((fn), _desc, _orig, MED_N)); \
	fn_free(_desc); fn_free(_orig); \
	/* large random */ \
	_lg     = make_rand_arr(LARGE_N, (seed) ^ 0xFFFF); \
	_lgorig = copy_arr(_lg, LARGE_N); \
	t_check((label "_large"), verify_sort((fn), _lg, _lgorig, LARGE_N)); \
	fn_free(_lg); fn_free(_lgorig); \
	/* edge cases */ \
	edge_size0_size1((label), (fn)); \
} while (0)

/* ---- individual sort wrappers ------------------------------------------ */

static void	wrap_insertion(int *arr, int n)
{
	if (n > 0)
		insertion_sort(arr, 0, n - 1);
}

static void	wrap_merge(int *arr, int n)
{
	if (n > 0)
		ft_merge_sort(arr, 0, n - 1);
}

static void	wrap_bubble(int *arr, int n)
{
	ft_bubble_sort(arr, n);
}

static void	wrap_selection(int *arr, int n)
{
	ft_selection_sort(arr, n);
}

static void	wrap_shell(int *arr, int n)
{
	shell_sort(arr, n);
}

static void	wrap_heap(int *arr, int n)
{
	heap_sort(arr, n);
}

static void	wrap_tim(int *arr, int n)
{
	tim_sort(arr, n);
}

static void	wrap_intro(int *arr, int n)
{
	intro_sort(arr, n);
}

static void	wrap_gnome(int *arr, int n)
{
	ft_gnome_sort(arr, n);
}

static void	wrap_comb(int *arr, int n)
{
	comb_sort(arr, n);
}

static void	wrap_cocktail(int *arr, int n)
{
	cocktail_shaker_sort(arr, n);
}

static void	wrap_odd_even(int *arr, int n)
{
	odd_even_sort(arr, n);
}

static void	wrap_three_way(int *arr, int n)
{
	three_way_merge_sort(arr, n);
}

/* counting/pigeonhole: small value range mandatory */
static void	wrap_counting(int *arr, int n)
{
	counting_sort(arr, n);
}

static void	wrap_pigeonhole(int *arr, int n)
{
	pigeonhole_sort(arr, n);
}

/* radix_sort(arr, size, max_bits): works on non-negative ints */
static void	wrap_radix(int *arr, int n)
{
	int	max_val;
	int	max_bits;
	int	i;

	if (!arr || n <= 1)
		return ;
	max_val = arr[0];
	i = 1;
	while (i < n)
	{
		if (arr[i] > max_val)
			max_val = arr[i];
		i++;
	}
	max_bits = 0;
	while (max_val > 0)
	{
		max_bits++;
		max_val >>= 1;
	}
	if (max_bits == 0)
		max_bits = 1;
	radix_sort(arr, n, max_bits);
}

/* ksort uses a window parameter k; test with k = n/4 */
static void	wrap_ksort(int *arr, int n)
{
	int	k;

	k = n / 4;
	if (k < 1)
		k = 1;
	ksort(arr, n, k);
}

/* ---- counting/pigeonhole small-range battery (separate helper) ---------- */

#define SMALL_BATTERY(label, fn, seed) do { \
	int *_arr; int *_orig; int *_eq; int *_asc; int *_desc; \
	_arr  = make_rand_small_arr(MED_N, (seed)); \
	_orig = copy_arr(_arr, MED_N); \
	t_check((label "_med"), verify_sort((fn), _arr, _orig, MED_N)); \
	fn_free(_arr); fn_free(_orig); \
	_eq = make_equal_arr(100, 3); \
	t_check((label "_equal"), verify_sort((fn), _eq, _eq, 100)); \
	fn_free(_eq); \
	_asc = make_asc_arr(100); \
	_orig = copy_arr(_asc, 100); \
	t_check((label "_asc"), verify_sort((fn), _asc, _orig, 100)); \
	fn_free(_asc); fn_free(_orig); \
	_desc = make_desc_arr(100); \
	_orig = copy_arr(_desc, 100); \
	t_check((label "_desc"), verify_sort((fn), _desc, _orig, 100)); \
	fn_free(_desc); fn_free(_orig); \
	edge_size0_size1((label), (fn)); \
} while (0)

/* ---- radix small-range battery (non-negative, small) ------------------- */

#define RADIX_BATTERY(label, fn, seed) SMALL_BATTERY(label, fn, seed)

/* ---- individual test functions ----------------------------------------- */

static void	test_insertion_sort(void)
{
	SORT_BATTERY("insertion", wrap_insertion, 0x1111);
}

static void	test_merge_sort(void)
{
	SORT_BATTERY("merge", wrap_merge, 0x2222);
}

static void	test_bubble_sort(void)
{
	/* bubble is O(n^2) — skip large */
	int	*arr;
	int	*orig;
	int	*eq;

	arr  = make_rand_arr(MED_N, 0x3333);
	orig = copy_arr(arr, MED_N);
	t_check("bubble_med", verify_sort(wrap_bubble, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	eq = make_equal_arr(MED_N, 5);
	t_check("bubble_equal", verify_sort(wrap_bubble, eq, eq, MED_N));
	fn_free(eq);
	arr = make_asc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("bubble_asc", verify_sort(wrap_bubble, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	arr = make_desc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("bubble_desc", verify_sort(wrap_bubble, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	edge_size0_size1("bubble", wrap_bubble);
}

static void	test_selection_sort(void)
{
	/* selection is O(n^2) — skip large */
	int	*arr;
	int	*orig;
	int	*eq;

	arr  = make_rand_arr(MED_N, 0x4444);
	orig = copy_arr(arr, MED_N);
	t_check("selection_med", verify_sort(wrap_selection, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	eq = make_equal_arr(MED_N, 0);
	t_check("selection_equal", verify_sort(wrap_selection, eq, eq, MED_N));
	fn_free(eq);
	arr = make_desc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("selection_desc", verify_sort(wrap_selection, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	edge_size0_size1("selection", wrap_selection);
}

static void	test_shell_sort(void)
{
	SORT_BATTERY("shell", wrap_shell, 0x5555);
}

static void	test_heap_sort(void)
{
	SORT_BATTERY("heap", wrap_heap, 0x6666);
}

static void	test_tim_sort(void)
{
	SORT_BATTERY("tim", wrap_tim, 0x7777);
}

static void	test_intro_sort(void)
{
	SORT_BATTERY("intro", wrap_intro, 0x8888);
}

static void	test_gnome_sort(void)
{
	/* gnome is O(n^2) — skip large */
	int	*arr;
	int	*orig;

	arr  = make_rand_arr(MED_N, 0x9999);
	orig = copy_arr(arr, MED_N);
	t_check("gnome_med", verify_sort(wrap_gnome, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	arr = make_desc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("gnome_desc", verify_sort(wrap_gnome, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	edge_size0_size1("gnome", wrap_gnome);
}

static void	test_comb_sort(void)
{
	SORT_BATTERY("comb", wrap_comb, 0xAAAA);
}

static void	test_cocktail_sort(void)
{
	/* cocktail is O(n^2) — skip large */
	int	*arr;
	int	*orig;

	arr  = make_rand_arr(MED_N, 0xBBBB);
	orig = copy_arr(arr, MED_N);
	t_check("cocktail_med", verify_sort(wrap_cocktail, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	arr = make_desc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("cocktail_desc", verify_sort(wrap_cocktail, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	edge_size0_size1("cocktail", wrap_cocktail);
}

static void	test_odd_even_sort(void)
{
	/* odd_even is O(n^2) — skip large */
	int	*arr;
	int	*orig;

	arr  = make_rand_arr(MED_N, 0xCCCC);
	orig = copy_arr(arr, MED_N);
	t_check("odd_even_med", verify_sort(wrap_odd_even, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	arr = make_desc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("odd_even_desc", verify_sort(wrap_odd_even, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	edge_size0_size1("odd_even", wrap_odd_even);
}

static void	test_three_way_merge(void)
{
	SORT_BATTERY("three_way", wrap_three_way, 0xDDDD);
}

static void	test_counting_sort(void)
{
	SMALL_BATTERY("counting", wrap_counting, 0xEEEE);
}

static void	test_pigeonhole_sort(void)
{
	SMALL_BATTERY("pigeonhole", wrap_pigeonhole, 0xF0F0);
}

static void	test_radix_sort(void)
{
	RADIX_BATTERY("radix", wrap_radix, 0x1F1F);
}

static void	test_ksort(void)
{
	int	*arr;
	int	*orig;
	int	*lg;
	int	*lgorig;
	int	*eq;

	arr  = make_rand_arr(MED_N, 0x2A2A);
	orig = copy_arr(arr, MED_N);
	t_check("ksort_med", verify_sort(wrap_ksort, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	eq = make_equal_arr(MED_N, 3);
	t_check("ksort_equal", verify_sort(wrap_ksort, eq, eq, MED_N));
	fn_free(eq);
	arr = make_desc_arr(MED_N);
	orig = copy_arr(arr, MED_N);
	t_check("ksort_desc", verify_sort(wrap_ksort, arr, orig, MED_N));
	fn_free(arr); fn_free(orig);
	lg     = make_rand_arr(LARGE_N, 0x3B3B);
	lgorig = copy_arr(lg, LARGE_N);
	t_check("ksort_large", verify_sort(wrap_ksort, lg, lgorig, LARGE_N));
	fn_free(lg); fn_free(lgorig);
	edge_size0_size1("ksort", wrap_ksort);
}

int	main(void)
{
	t_begin("sort");
	t_reseed(0x5EED5074ULL);
	test_insertion_sort();
	test_merge_sort();
	test_bubble_sort();
	test_selection_sort();
	test_shell_sort();
	test_heap_sort();
	test_tim_sort();
	test_intro_sort();
	test_gnome_sort();
	test_comb_sort();
	test_cocktail_sort();
	test_odd_even_sort();
	test_three_way_merge();
	test_counting_sort();
	test_pigeonhole_sort();
	test_radix_sort();
	test_ksort();
	return (t_end());
}
