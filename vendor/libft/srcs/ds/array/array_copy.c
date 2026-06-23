/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:07:54 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:26:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "ft_string.h"

t_arr	*array_copy(t_arr *a)
{
	t_arr		*cpy;
	t_arr_elem	*ae;
	t_arr_elem	*new;

	if (a == 0)
		return ((t_arr *) NULL);
	cpy = array_create();
	cpy->max_idx = a->max_idx;
	cpy->nelem = a->nelem;
	ae = element_forw(a->head);
	while (ae != a->head)
	{
		if (element_value(ae))
			new = array_create_element(element_index(ae),
					ft_strdup(element_value(ae)));
		else
			new = array_create_element(element_index(ae), NULL);
		add_before(cpy->head, new);
		if (ae == lastref(a))
			set_lastref(cpy, new);
		ae = element_forw(ae);
	}
	return (cpy);
}
