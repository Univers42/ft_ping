/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_create_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:05:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:21:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/**
 * Allocate and return a new array element with index INDEX and value VALUE.
 */
t_arr_elem	*array_create_element(size_t idx, char *value)
{
	t_arr_elem	*r;

	r = (t_arr_elem *)fn_malloc(sizeof(t_arr_elem));
	if (!r)
		return (NULL);
	r->ind = idx;
	r->val = value;
	r->next = (t_arr_elem *) NULL;
	r->prev = (t_arr_elem *) NULL;
	return (r);
}
