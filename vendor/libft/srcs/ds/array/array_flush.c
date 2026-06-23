/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:39:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:50:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	array_flush(t_arr *a)
{
	register t_arr_elem	*r;
	register t_arr_elem	*r1;

	if (a == 0)
		return ;
	r = element_forw(a->head);
	while (r != a->head)
	{
		r1 = element_forw(r);
		array_dispose_element(r);
		r = r1;
	}
	a->head->next = a->head;
	a->head->prev = a->head;
	a->max_idx = (size_t)-1;
	a->nelem = 0;
	invalidate_lastref(a);
}
