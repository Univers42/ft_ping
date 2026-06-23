/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 01:51:48 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/25 20:44:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qsort.h"

/* partition the range [low, high] using metas and return pivot index */
size_t	partition(t_intern *metas)
{
	void	*pv;
	size_t	i;
	size_t	j;
	int		cmp;

	pv = fn_malloc(metas->size);
	if (!pv)
		return (metas->low);
	ft_memcpy(pv, metas->basep + metas->high * metas->size, metas->size);
	i = metas->low;
	j = metas->low;
	while (j < metas->high)
	{
		cmp = metas->compar(metas->basep + j * metas->size, pv);
		if (cmp < 0)
		{
			swap_elems(metas, i, j);
			i++;
		}
		j++;
	}
	return (swap_elems(metas, i, metas->high), fn_free(pv), i);
}

#ifdef QSORT_RECURSIVE

/* public ft_qsort: recursive version (uses qsort_rec) */
void	ft_qsort(void *base, size_t nmemb, size_t size,
				int (*compar)(const void *, const void *))
{
	t_intern	metas;

	if (nmemb < 2 || size == 0)
		return ;
	metas.basep = (char *)base;
	metas.low = 0;
	metas.high = nmemb - 1;
	metas.size = size;
	metas.compar = compar;
	metas.tmp = fn_malloc(size);
	if (!metas.tmp)
		return ;
	qsort_rec(&metas);
	fn_free(metas.tmp);
}
#else

/* allocate stack: try dynamic allocation, fallback to static buffer */
static t_intern	*alloc_stack(size_t nmemb, size_t *cap, int *is_dynamic)
{
	t_intern			*stack;
	size_t				want;
	static t_intern		small_stack[64];

	*is_dynamic = 0;
	want = 1;
	if (nmemb > 1)
		want = nmemb;
	stack = fn_malloc(want * sizeof(*stack));
	if (stack)
	{
		*cap = want;
		*is_dynamic = 1;
		return (stack);
	}
	*cap = 64;
	return (small_stack);
}

/* pop one entry and process it (partition + push children) */
static void	process_top(t_intern *stack, size_t *sp, size_t cap)
{
	t_intern	cur;
	size_t		p;
	t_pushctx	ctx;

	if (*sp == 0)
		return ;
	(*sp)--;
	cur = stack[*sp];
	if (cur.low >= cur.high)
		return ;
	p = partition(&cur);
	ctx.stack = stack;
	ctx.sp = sp;
	ctx.cap = cap;
	ctx.cur = &cur;
	ctx.p = p;
	push_children(&ctx);
}

/* iterative, stack-based ft_qsort to limit recursion depth; uses helpers */
void	ft_qsort(void *base, size_t nmemb, size_t size,
				int (*compar)(const void *, const void *))
{
	t_intern	metas;
	t_intern	*stack;
	size_t		cap;
	size_t		sp;
	int			is_dynamic;

	if (nmemb < 2 || size == 0)
		return ;
	metas.basep = (char *)base;
	metas.low = 0;
	metas.high = nmemb - 1;
	metas.size = size;
	metas.compar = compar;
	metas.tmp = fn_malloc(size);
	if (!metas.tmp)
		return ;
	stack = alloc_stack(nmemb, &cap, &is_dynamic);
	stack[0] = metas;
	sp = 1;
	while (sp > 0)
		process_top(stack, &sp, cap);
	if (is_dynamic)
		fn_free(stack);
	fn_free(metas.tmp);
}

#endif
