/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_value_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:57:31 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:10:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/*
 * Replace the value of element at index 'i' with 'v'.
 * Parameters:
 *  - a: target array
 *  - i: element index to replace
 *  - v: new value (taken ownership on success)
 *  - old: optional out parameter receiving previous value (may be NULL)
 *
 * Returns 0 on success, -1 on error or if index not found.
 */
int	array_value_replace(t_arr *a, size_t i, char *v, char **old)
{
	t_arr_elem	*ae;
	char		*prev;

	if (!a || !v)
		return (-1);
	ae = element_forw(a->head);
	while (ae != a->head)
	{
		if (element_index(ae) == i)
		{
			prev = ae->val;
			ae->val = v;
			if (old)
				*old = prev;
			else
				fn_free(prev);
			set_lastref(a, ae);
			return (0);
		}
		ae = element_forw(ae);
	}
	return (fn_free(v), -1);
}
