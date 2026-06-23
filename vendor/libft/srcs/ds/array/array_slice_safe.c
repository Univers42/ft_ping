/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_slice_safe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:39:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_arr	*array_slice_safe(t_arr *array, size_t start, size_t end)
{
	t_arr_elem	*s;
	t_arr_elem	*e;
	size_t		i;

	if (!array || array_empty(array) || start >= array_num_elements(array))
		return (array_create());
	s = element_forw(array->head);
	i = -1;
	while (++i < start && s != array->head)
		s = element_forw(s);
	if (s == array->head)
		return (array_create());
	e = s;
	i = start - 1;
	while (++i < end && e != array->head)
		e = element_forw(e);
	return (array_slice(array, s, e));
}
