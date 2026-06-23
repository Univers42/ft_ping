/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lastref.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:09:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:49:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	set_lastref(t_arr *a, t_arr_elem *e)
{
	if (!a)
		return ;
	if (e == NULL || e == a->head)
		a->lastref = NULL;
	else
		a->lastref = e;
}
