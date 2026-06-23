/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_walk_and_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:11:52 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:40:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/* Insert before AE and update array metadata. */
int	as_insert_before_and_fix(t_arr *a, t_arr_elem *ae, t_arr_elem *elem)
{
	if (!a || !ae || !elem)
		return (-1);
	add_before(ae, elem);
	as_renumber_indices(a);
	set_lastref(a, element_forw(a->head));
	return (0);
}

/* Insert after AE and update array metadata. */
static int	as_insert_after_and_fix(t_arr *a, t_arr_elem *ae, t_arr_elem *elem)
{
	if (!a || !ae || !elem)
		return (-1);
	add_after(ae, elem);
	as_renumber_indices(a);
	set_lastref(a, element_forw(a->head));
	return (0);
}

/* Walk forward and perform replace or insertion. */
static int	as_walk_forward_and_insert(t_as_insert_ctx *ctx)
{
	t_arr_elem	*ae;

	if (!ctx || !ctx->a || !ctx->start || !ctx->elem)
		return (-1);
	ae = ctx->start;
	while (ae != ctx->a->head)
	{
		if (element_index(ae) == ctx->idx)
			if (as_replace_elem_value(ctx->a, ae, ctx->elem) == 0)
				return (0);
		if (element_index(ae) > ctx->idx)
			if (as_insert_before_and_fix(ctx->a, ae, ctx->elem) == 0)
				return (0);
		ae = element_forw(ae);
	}
	return (-1);
}

/* Walk backward and perform replace or insertion. */
static int	as_walk_backward_and_insert(t_as_insert_ctx *ctx)
{
	t_arr_elem	*ae;

	if (!ctx || !ctx->a || !ctx->start || !ctx->elem)
		return (-1);
	ae = ctx->start;
	while (ae != ctx->a->head)
	{
		if (element_index(ae) == ctx->idx)
			if (as_replace_elem_value(ctx->a, ae, ctx->elem) == 0)
				return (0);
		if (element_index(ae) < ctx->idx)
			if (as_insert_after_and_fix(ctx->a, ae, ctx->elem) == 0)
				return (0);
		ae = element_back(ae);
	}
	return (-1);
}

/* Dispatcher kept short to respect line limits. */
int	as_walk_and_insert(t_as_insert_ctx *ctx)
{
	if (!ctx || !ctx->a || !ctx->start || !ctx->elem)
		return (-1);
	if (ctx->direction == 1)
		return (as_walk_forward_and_insert(ctx));
	return (as_walk_backward_and_insert(ctx));
}
