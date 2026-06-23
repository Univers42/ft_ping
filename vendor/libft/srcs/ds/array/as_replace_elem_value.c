/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_replace_elem_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:35:29 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:35:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

int	as_replace_elem_value(t_arr *a, t_arr_elem *ae, t_arr_elem *elem)
{
	char	*old;

	if (!a || !ae || !elem)
		return (-1);
	old = ae->val;
	ae->val = elem->val;
	elem->val = NULL;
	fn_free(old);
	array_dispose_element(elem);
	set_lastref(a, ae);
	return (0);
}
