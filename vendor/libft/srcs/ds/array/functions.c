/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:05:45 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:35:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/*
 * Reusable helper: return first (lowest-index) element of array or NULL.
 */
t_arr_elem	*as_get_first_elem(t_arr *a)
{
	if (a == NULL || array_empty(a))
		return (NULL);
	return (element_forw(a->head));
}

/*
 * Not generally reusable: detach element and extract its value into out.
 * Leaves ownership of the returned string to the caller.
 */
int	as_detach_and_extract(t_arr *a, t_arr_elem *el, char **out)
{
	if (a == NULL || el == NULL || out == NULL)
		return (-1);
	el->prev->next = el->next;
	el->next->prev = el->prev;
	*out = el->val;
	el->val = NULL;
	array_dispose_element(el);
	return (0);
}

/*
 * Reusable helper: renumber indices and update metadata, invalidate lastref.
 */
void	as_renumber_indices(t_arr *a)
{
	t_arr_elem	*cur;
	size_t		idx;

	if (!a)
		return ;
	idx = 0;
	cur = element_forw(a->head);
	while (cur != a->head)
	{
		cur->ind = idx++;
		cur = element_forw(cur);
	}
	a->nelem = idx;
	a->first_idx = 0;
	a->max_idx = (size_t)-1;
	if (idx > 0)
	{
		a->first_idx = element_index(a->head->next);
		a->max_idx = element_index(a->head->prev);
	}
	invalidate_lastref(a);
}

/*
 * Handle simple edge cases:
 * - empty array
 * - append at end (i > max)
 * - insert before first (i < first)
 *
 * Returns 1 if handled (success), 0 if not handled, -1 on error.
 * Specific to insert semantics.
 */
int	as_handle_edge_insert(t_arr *a, size_t i, t_arr_elem *elem)
{
	if (!a || !elem)
		return (-1);
	if (array_empty(a))
	{
		add_before(a->head, elem);
		as_renumber_indices(a);
		set_lastref(a, element_forw(a->head));
		return (1);
	}
	if (i > array_max_index(a))
	{
		add_before(a->head, elem);
		as_renumber_indices(a);
		set_lastref(a, a->head->prev);
		return (1);
	}
	if (i < array_first_index(a))
	{
		add_after(a->head, elem);
		as_renumber_indices(a);
		set_lastref(a, a->head->next);
		return (1);
	}
	return (0);
}

/*
 * Choose a start element and traversal direction based on lastref optimisation.
 * Reusable in the sense it only inspects metadata and returns choices.
 */
void	as_choose_start_direction(t_arr *a, size_t i, t_arr_elem **start,
			int *direction)
{
	t_arr_elem	*st;
	size_t		startind;

	if (!a || !start || !direction)
		return ;
	st = lastref(a);
	if (st == NULL || st == a->head)
		st = element_forw(a->head);
	startind = element_index(st);
	if (i < startind / 2)
	{
		*start = element_forw(a->head);
		*direction = 1;
		return ;
	}
	if (i >= startind)
		*direction = 1;
	else
		*direction = -1;
	*start = st;
}
