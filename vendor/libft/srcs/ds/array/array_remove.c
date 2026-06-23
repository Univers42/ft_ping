/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:47:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:52:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/* Reusable: search for element with index idx starting at 'start'
going in 'direction'.
 * Returns the element if found, NULL otherwise.
 */
static t_arr_elem	*as_find_element_from(t_arr *a, t_arr_elem *start,
										int direction, size_t idx)
{
	t_arr_elem	*ae;

	if (!a || !start)
		return (NULL);
	ae = start;
	while (ae != a->head)
	{
		if (element_index(ae) == idx)
			return (ae);
		if (direction == 1)
		{
			ae = element_forw(ae);
			if (ae != a->head && element_index(ae) > idx)
				break ;
		}
		else
		{
			ae = element_back(ae);
			if (ae != a->head && element_index(ae) < idx)
				break ;
		}
	}
	return (NULL);
}

/* Specific: unlink element AE from list, adjust counts and renumber indices. */
static void	ar_unlink_and_fix(t_arr *a, t_arr_elem *ae)
{
	if (!a || !ae)
		return ;
	ae->next->prev = ae->prev;
	ae->prev->next = ae->next;
	if (a->nelem > 0)
		a->nelem--;
	as_renumber_indices(a);
	if (ae->next != a->head)
		set_lastref(a, ae->next);
	else if (ae->prev != a->head)
		set_lastref(a, ae->prev);
	else
		invalidate_lastref(a);
}

/* Top-level: compact and norm-compliant. */
t_arr_elem	*array_remove(t_arr *a, size_t i)
{
	t_arr_elem	*start;
	int			direction;
	t_arr_elem	*ae;

	if (a == NULL || array_empty(a))
		return (NULL);
	if (i > array_max_index(a) || i < array_first_index(a))
		return (NULL);
	as_choose_start_direction(a, i, &start, &direction);
	ae = as_find_element_from(a, start, direction, i);
	if (ae == NULL)
		return (NULL);
	ar_unlink_and_fix(a, ae);
	return (ae);
}
