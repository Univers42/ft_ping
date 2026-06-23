/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elem_by_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:35:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 01:50:45 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_arr_elem	*find_elem_by_index(t_arr *a, size_t idx)
{
	t_arr_elem	*cur;

	if (!a || array_empty(a))
		return (NULL);
	cur = element_forw(a->head);
	while (cur != a->head)
	{
		if (element_index(cur) == idx)
			return (cur);
		cur = element_forw(cur);
	}
	return (NULL);
}
