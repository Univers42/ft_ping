/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_unshift_element.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:39:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:23:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_arr_elem	*array_unshift_element(t_arr *a)
{
	t_arr_elem	*first;

	if (a == NULL || array_empty(a))
		return (NULL);
	first = as_get_first_elem(a);
	if (first == NULL || first == a->head)
		return (NULL);
	return (array_remove(a, element_index(first)));
}
