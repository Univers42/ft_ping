/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:21:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:00:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/* Prototypes for helpers placed in functions.c */
t_arr_elem	*as_get_first_elem(t_arr *a);
int			as_detach_and_extract(t_arr *a, t_arr_elem *el, char **out);
void		as_renumber_indices(t_arr *a);

int	array_shift(t_arr *a, char **out)
{
	t_arr_elem	*first;

	if (a == NULL || out == NULL)
		return (-1);
	if (array_empty(a))
		return (-1);
	first = as_get_first_elem(a);
	if (first == NULL)
		return (-1);
	if (as_detach_and_extract(a, first, out) != 0)
		return (-1);
	as_renumber_indices(a);
	if (!array_empty(a))
		set_lastref(a, element_forw(a->head));
	else
		invalidate_lastref(a);
	return (0);
}
