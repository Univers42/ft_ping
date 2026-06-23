/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:05:45 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:34:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/* Prototypes for helpers implemented in functions.c */
int		as_handle_edge_insert(t_arr *a, size_t i, t_arr_elem *new);
void	as_choose_start_direction(t_arr *a, size_t i, t_arr_elem **start,
			int *direction);

int	array_insert(t_arr *a, size_t i, char *v)
{
	t_arr_elem		*elem;
	int				handled;
	t_arr_elem		*start;
	int				direction;
	t_as_insert_ctx	ctx;

	if (a == NULL)
		return (-1);
	elem = array_create_element(i, v);
	if (elem == NULL)
		return (-1);
	handled = as_handle_edge_insert(a, i, elem);
	if (handled != 0)
	{
		if (handled == -1)
			array_dispose_element(elem);
		return (handled);
	}
	as_choose_start_direction(a, i, &start, &direction);
	ctx = (t_as_insert_ctx){a, start, direction, i, elem};
	if (as_walk_and_insert(&ctx) == 0)
		return (0);
	return (array_dispose_element(elem), invalidate_lastref(a), -1);
}
