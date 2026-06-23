/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_slice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:15:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:51:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "ft_string.h"

t_arr	*array_slice(t_arr *array, t_arr_elem *s, t_arr_elem *e)
{
	t_arr		*a;
	t_arr_elem	*p;
	t_arr_elem	*n;
	size_t		i;
	size_t		mi;

	(void)array;
	a = array_create();
	mi = 0;
	p = s;
	i = 0;
	while (p != e)
	{
		n = array_create_element(element_index(p), NULL);
		if (element_value(p))
			n = array_create_element(element_index(p),
					ft_strdup(element_value(p)));
		add_before(a->head, n);
		mi = element_index(n);
		p = element_forw(p);
		i++;
	}
	a->nelem = i;
	a->max_idx = mi;
	return (a);
}
