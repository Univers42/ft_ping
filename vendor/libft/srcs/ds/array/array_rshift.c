/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_rshift.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:36:09 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:32:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

static void	renumber_indices(t_arr *a)
{
	t_arr_elem	*cur;
	size_t		idx;

	idx = 0;
	if (!a)
		return ;
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

int	array_rshift(t_arr *a, int n, char *s)
{
	t_arr_elem	*ae;
	t_arr_elem	*new;

	if (a == 0 || (array_empty(a) && s == 0))
		return (0);
	else if (n <= 0)
		return (a->nelem);
	ae = element_forw(a->head);
	if (s)
	{
		new = array_create_element(0, s);
		add_before(ae, new);
		renumber_indices(a);
		return (a->nelem);
	}
	renumber_indices(a);
	return (a->nelem);
}
