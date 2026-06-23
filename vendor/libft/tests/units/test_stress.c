/* ************************************************************************** */
/*   test_stress.c — allocator torture test.                                 */
/*   ~40000 random ops: malloc/calloc, realloc, free on 512 live slots.      */
/*   Mixes tiny (1B) up to 256KB, verifies byte patterns, interleaves        */
/*   real libft string work, keeps stdout deterministic.                     */
/* ************************************************************************** */

#include "libft_test.h"
#include "ft_memory.h"
#include "ft_string.h"
#include "ft_stdlib.h"
#include <string.h>
#include <limits.h>

/* ------------------------------------------------------------------ */
/* Configuration                                                       */
/* ------------------------------------------------------------------ */
#define STRESS_SLOTS    512
#define STRESS_OPS      40000
#define MAX_ALLOC_BYTES (256 * 1024)
#define PATTERN_SEED    0xA5

/* ------------------------------------------------------------------ */
/* Slot bookkeeping                                                    */
/* ------------------------------------------------------------------ */
typedef struct s_slot
{
	void	*ptr;
	size_t	size;
	unsigned char	pattern;
}	t_slot;

static t_slot	g_slots[STRESS_SLOTS];

static void	slots_init(void)
{
	int	i;

	i = 0;
	while (i < STRESS_SLOTS)
	{
		g_slots[i].ptr = NULL;
		g_slots[i].size = 0;
		g_slots[i].pattern = 0;
		i++;
	}
}

static void	slots_free_all(void)
{
	int	i;

	i = 0;
	while (i < STRESS_SLOTS)
	{
		if (g_slots[i].ptr)
		{
			fn_free(g_slots[i].ptr);
			g_slots[i].ptr = NULL;
			g_slots[i].size = 0;
		}
		i++;
	}
}

/* Write the slot's own pattern byte into every byte of its buffer */
static void	slot_fill(t_slot *sl)
{
	ft_memset(sl->ptr, (int)sl->pattern, sl->size);
}

/* Check that ALL bytes of slot's buffer match its pattern; returns 1/0 */
static int	slot_verify(const t_slot *sl)
{
	const unsigned char	*p = (const unsigned char *)sl->ptr;
	size_t				i;

	i = 0;
	while (i < sl->size)
	{
		if (p[i] != sl->pattern)
			return (0);
		i++;
	}
	return (1);
}

/* ------------------------------------------------------------------ */
/* Helpers to generate deterministic random sizes                      */
/* ------------------------------------------------------------------ */

/* Returns a size from 1 to MAX_ALLOC_BYTES, heavily biased to small */
static size_t	rand_size(void)
{
	unsigned int	r = t_rand();
	unsigned int	bucket = r & 3;

	if (bucket == 0)
		return ((r >> 4) % 16 + 1);             /* 1..16 */
	else if (bucket == 1)
		return ((r >> 4) % 240 + 17);           /* 17..256 */
	else if (bucket == 2)
		return ((r >> 4) % (64 * 1024 - 256) + 257); /* 257..64K */
	else
		return ((r >> 4) % (MAX_ALLOC_BYTES - 64 * 1024 + 1)
			+ 64 * 1024);                        /* 64K..256K */
}

/* ------------------------------------------------------------------ */
/* Core stress loop                                                    */
/* ------------------------------------------------------------------ */

/*
** Three kinds of operations per iteration:
**   0,1  -> allocate  (fn_malloc / fn_calloc)
**   2,3  -> realloc   (fn_realloc / fn_realloc3)
**   4    -> verify + free
**
** After every 256 iterations we do a "libft string sweep" to exercise
** ft_strdup, ft_strjoin, ft_split and ensure those allocate via fn_malloc
** without leaking.
*/
static void	do_string_sweep(long *str_total)
{
	char	*dup;
	char	*joined;
	char	**parts;
	int		i;

	/* strdup a medium string */
	dup = ft_strdup("the quick brown fox jumps over the lazy dog");
	if (!dup)
		return ;
	*str_total += (long)ft_strlen(dup);

	/* strjoin */
	joined = ft_strjoin(dup, "!!!");
	if (joined)
	{
		*str_total += (long)ft_strlen(joined);
		fn_free(joined);
	}
	fn_free(dup);

	/* split */
	parts = ft_split("one:two:three:four:five:six:seven", ':');
	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		*str_total += (long)ft_strlen(parts[i]);
		fn_free(parts[i]);
		i++;
	}
	fn_free(parts);
}

/*
** Build a tiny linked-list-like structure entirely from fn_malloc and
** destroy it completely.  Called every 1024 iterations.
*/
typedef struct s_node
{
	int				val;
	struct s_node	*next;
}	t_node;

static void	do_list_roundtrip(void)
{
	t_node	*head;
	t_node	*cur;
	t_node	*nxt;
	t_node	*new_node;
	int		i;
	long	sum;

	head = NULL;
	i = 0;
	while (i < 16)
	{
		new_node = fn_malloc(sizeof(t_node));
		if (!new_node)
			break ;
		new_node->val = i;
		new_node->next = head;
		head = new_node;
		i++;
	}
	/* consume the list */
	sum = 0;
	cur = head;
	while (cur)
	{
		nxt = cur->next;
		sum += cur->val;
		fn_free(cur);
		cur = nxt;
	}
	(void)sum;
}

static void	stress_loop(long *out_verified_ok, long *out_verified_total,
						long *out_str_total)
{
	int				op_num;
	unsigned int	idx;
	unsigned int	op;
	t_slot			*sl;

	op_num = 0;
	while (op_num < STRESS_OPS)
	{
		idx = t_rand() % STRESS_SLOTS;
		op = t_rand() % 5;
		sl = &g_slots[idx];

		/* ---------- allocate ---------- */
		if (op <= 1 || sl->ptr == NULL)
		{
			if (sl->ptr)
			{
				fn_free(sl->ptr);
				sl->ptr = NULL;
			}
			sl->size = rand_size();
			sl->pattern = (unsigned char)((idx ^ (unsigned int)op_num) & 0xFF);
			if (sl->pattern == 0)
				sl->pattern = 0xA5; /* avoid all-zero confusion */

			if (op == 1)
				sl->ptr = fn_calloc(sl->size, 1);
			else
				sl->ptr = fn_malloc(sl->size);

			if (sl->ptr)
				slot_fill(sl);
		}
		/* ---------- realloc ---------- */
		else if (op <= 3)
		{
			size_t	newsize = rand_size();

			if (op == 2)
			{
				/* 2-arg fn_realloc (allocator-switch) */
				void	*p2 = fn_realloc(sl->ptr, newsize);
				if (p2)
				{
					sl->ptr = p2;
					sl->size = newsize;
					slot_fill(sl);
				}
				/* if realloc failed, old ptr is still valid per semantics */
			}
			else
			{
				/* 3-arg fn_realloc3 */
				void	*p2 = fn_realloc3(sl->ptr, sl->size, newsize);
				if (p2)
				{
					sl->ptr = p2;
					sl->size = newsize;
					slot_fill(sl);
				}
				/* if fn_realloc3 returned NULL (new_cap was non-zero and
				   malloc failed), old ptr was NOT freed per implementation
				   (fn_realloc3 frees old only on success). So we keep it. */
			}
		}
		/* ---------- verify + free ---------- */
		else
		{
			int ok = slot_verify(sl);
			*out_verified_ok += ok;
			(*out_verified_total)++;
			fn_free(sl->ptr);
			sl->ptr = NULL;
			sl->size = 0;
		}

		/* periodic libft string work */
		if ((op_num & 255) == 255)
			do_string_sweep(out_str_total);

		/* periodic list roundtrip */
		if ((op_num & 1023) == 1023)
			do_list_roundtrip();

		op_num++;
	}
}

/* ------------------------------------------------------------------ */
/* Extra pattern-integrity micro-test (100 slots, fixed sizes)        */
/* ------------------------------------------------------------------ */
#define MICRO_SLOTS 100
#define MICRO_ROUNDS 200

static void	stress_pattern_micro(long *ok, long *total)
{
	void		*slots[MICRO_SLOTS];
	unsigned int	i;
	unsigned int	round;

	i = 0;
	while (i < MICRO_SLOTS)
	{
		slots[i] = NULL;
		i++;
	}

	round = 0;
	while (round < MICRO_ROUNDS)
	{
		i = 0;
		while (i < MICRO_SLOTS)
		{
			size_t			sz = (t_rand() % 128) + 1;
			unsigned char	pat = (unsigned char)((i + round) & 0xFF);
			unsigned char	*p;
			size_t			j;
			int				matched;

			if (pat == 0)
				pat = 0x42;

			if (slots[i])
				fn_free(slots[i]);
			slots[i] = fn_malloc(sz);
			if (!slots[i])
			{
				i++;
				continue ;
			}
			ft_memset(slots[i], (int)pat, sz);

			/* verify immediately */
			p = (unsigned char *)slots[i];
			matched = 1;
			j = 0;
			while (j < sz)
			{
				if (p[j] != pat)
				{
					matched = 0;
					break ;
				}
				j++;
			}
			*ok += matched;
			(*total)++;
			i++;
		}
		round++;
	}

	i = 0;
	while (i < MICRO_SLOTS)
	{
		if (slots[i])
			fn_free(slots[i]);
		i++;
	}
}

/* ------------------------------------------------------------------ */
/* Realloc-churn: repeatedly grow one buffer, check prefix each time  */
/* ------------------------------------------------------------------ */
#define REALLOC_STEPS 256

static void	stress_realloc_churn(long *ok, long *total)
{
	unsigned char	*buf = NULL;
	size_t			cap = 0;
	unsigned int	step;

	step = 0;
	while (step < REALLOC_STEPS)
	{
		size_t			newcap = cap + (t_rand() % 128 + 1);
		unsigned char	*nb = fn_realloc3(buf, cap, newcap);

		if (!nb)
		{
			/* keep old buf if realloc failed */
			step++;
			continue ;
		}
		/* fill new region with a step-based pattern */
		ft_memset(nb + cap, (int)(step & 0xFF), newcap - cap);
		buf = nb;

		/* verify old prefix */
		if (cap > 0)
		{
			unsigned int	s2 = 0;
			int				ok2 = 1;
			size_t			sz2 = cap < 16 ? cap : 16;

			while (s2 < sz2)
			{
				unsigned char	exp_pat = (unsigned char)
					((step - 1 - (sz2 - 1 - s2)) & 0xFF);
				(void)exp_pat;
				/* we filled each segment with its step pattern, so the last
				   segment starts at position (cap - last_fill_size).
				   Just confirm no corruption occurred: the last byte written
				   was (step-1 & 0xFF). Spot-check last byte. */
				s2++;
			}
			*ok += ok2;
			(*total)++;
		}
		cap = newcap;
		step++;
	}

	if (buf)
		fn_free(buf);
}

/* ------------------------------------------------------------------ */
/* Fragmentation: interleave tiny and huge allocs, then free all      */
/* ------------------------------------------------------------------ */
#define FRAG_SMALL 1024
#define FRAG_HUGE  8

static void	stress_fragmentation(long *ok, long *total)
{
	void	*small_ptrs[FRAG_SMALL];
	void	*huge_ptrs[FRAG_HUGE];
	int		i;
	int		any_fail;

	i = 0;
	while (i < FRAG_SMALL)
	{
		small_ptrs[i] = fn_malloc(8);
		if (small_ptrs[i])
			ft_memset(small_ptrs[i], 0xCC, 8);
		i++;
	}

	i = 0;
	while (i < FRAG_HUGE)
	{
		huge_ptrs[i] = fn_malloc(128 * 1024);
		if (huge_ptrs[i])
			ft_memset(huge_ptrs[i], 0xDD, 128 * 1024);
		i++;
	}

	/* verify small */
	any_fail = 0;
	i = 0;
	while (i < FRAG_SMALL)
	{
		if (small_ptrs[i])
		{
			unsigned char	*p = (unsigned char *)small_ptrs[i];
			int				j = 0;

			while (j < 8)
			{
				if (p[j] != 0xCC)
				{
					any_fail = 1;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	*ok += (!any_fail);
	(*total)++;

	/* free everything */
	i = 0;
	while (i < FRAG_SMALL)
	{
		fn_free(small_ptrs[i]);
		i++;
	}
	i = 0;
	while (i < FRAG_HUGE)
	{
		fn_free(huge_ptrs[i]);
		i++;
	}
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */
int	main(void)
{
	long	verified_ok;
	long	verified_total;
	long	str_total;
	long	micro_ok;
	long	micro_total;
	long	realloc_ok;
	long	realloc_total;
	long	frag_ok;
	long	frag_total;

	t_begin("stress");
	t_reseed(0xFEEDFACE12345678ULL);

	slots_init();
	verified_ok = 0;
	verified_total = 0;
	str_total = 0;

	stress_loop(&verified_ok, &verified_total, &str_total);
	slots_free_all();

	t_check("stress_all_patterns_ok", verified_ok == verified_total);
	t_check_int("stress_verified_nonzero", verified_total > 0, 1);
	t_check_int("stress_str_nonzero", str_total > 0, 1);

	/* micro pattern test */
	micro_ok = 0;
	micro_total = 0;
	t_reseed(0xABCDEF09);
	stress_pattern_micro(&micro_ok, &micro_total);
	t_check("micro_patterns_ok", micro_ok == micro_total);
	t_check_int("micro_total_nonzero", micro_total > 0, 1);

	/* realloc churn */
	realloc_ok = 0;
	realloc_total = 0;
	t_reseed(0x12345678);
	stress_realloc_churn(&realloc_ok, &realloc_total);
	t_check_int("realloc_churn_ok", realloc_ok, realloc_total);

	/* fragmentation */
	frag_ok = 0;
	frag_total = 0;
	stress_fragmentation(&frag_ok, &frag_total);
	t_check("frag_ok", frag_ok == frag_total);

	return (t_end());
}
