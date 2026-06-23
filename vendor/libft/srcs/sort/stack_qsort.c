/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_qsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:16:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 01:49:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qsort.h"

/* push one item on stack; returns 0 on overflow, 1 on success */
int	stack_push(t_intern *stack, size_t *sp, size_t cap, t_intern item)
{
	if (*sp >= cap)
		return (0);
	stack[(*sp)++] = item;
	return (1);
}

/* prepare and push a single child range (low..high) */
static void	push_single(t_pushctx *c, size_t low, size_t high)
{
	t_intern	tmp;

	if (low > high)
		return ;
	tmp = *c->cur;
	tmp.low = low;
	tmp.high = high;
	stack_push(c->stack, c->sp, c->cap, tmp);
}

/* push left partition then right partition (if present) */
static void	push_left_then_right(t_pushctx *c, size_t p)
{
	if (p > c->cur->low)
		push_single(c, c->cur->low, p - 1);
	if (c->cur->high > p)
		push_single(c, p + 1, c->cur->high);
}

/* push right partition then left partition (if present) */
static void	push_right_then_left(t_pushctx *c, size_t p)
{
	if (c->cur->high > p)
		push_single(c, p + 1, c->cur->high);
	if (p > c->cur->low)
		push_single(c, c->cur->low, p - 1);
}

/* push partition children: choose order that bounds stack depth */
void	push_children(t_pushctx *c)
{
	size_t	left_size;
	size_t	right_size;
	size_t	p;

	p = c->p;
	left_size = 0;
	if (p > c->cur->low)
		left_size = p - c->cur->low;
	right_size = 0;
	if (c->cur->high > p)
		right_size = c->cur->high - p;
	if (left_size <= right_size)
		push_left_then_right(c, p);
	else
		push_right_then_left(c, p);
}
