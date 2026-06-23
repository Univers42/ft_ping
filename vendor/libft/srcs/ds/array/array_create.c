/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:51:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:09:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_arr	*array_create(void)
{
	t_arr		*r;
	t_arr_elem	*head;

	r = (t_arr *)fn_malloc(sizeof(t_arr));
	if (!r)
		return (NULL);
	r->max_idx = (size_t)-1;
	r->nelem = 0;
	r->lastref = (t_arr_elem *)0;
	head = array_create_element((size_t)-1, (char *) NULL);
	if (!head)
		return (fn_free(r), NULL);
	head->next = head;
	head->prev = head;
	r->head = head;
	r->first_idx = 0;
	r->alloc_size = 0;
	r->elements = NULL;
	return (r);
}
