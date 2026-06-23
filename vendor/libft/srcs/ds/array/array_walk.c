/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_walk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:33:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:34:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	array_walk(t_arr *a, void *user, void (*func)(t_arr_elem *, void *))
{
	t_arr_elem	*cur;

	if (!a || array_empty(a) || !func)
		return ;
	cur = element_forw(a->head);
	while (cur != a->head)
	{
		func(cur, user);
		cur = element_forw(cur);
	}
}
