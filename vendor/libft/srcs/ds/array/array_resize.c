/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_resize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:48:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:48:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	array_resize(t_arr *a, size_t newsize)
{
	if (!a)
		return ;
	if (newsize == 0)
	{
		array_flush(a);
		return ;
	}
	if (a->elements && a->alloc_size < newsize)
	{
		a->elements = fn_realloc(a->elements, newsize * sizeof(t_arr_elem *));
		if (a->elements)
			a->alloc_size = newsize;
	}
}
