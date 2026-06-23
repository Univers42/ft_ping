/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_dequote_escapes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:15:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/30 21:04:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// t_arr *array_dequote_escapes(t_arr *array)
//{
//	t_arr_elem *a;
//	char *t;
//
//	if (array == 0 || array_head(array) == 0 || array_empty(array))
//		return (NULL);
//	a = element_forw(array->head);
//	while (a != array->head)
//	{
//		t = dequote_escapes(a->val);
//		free(a->val);
//		a->val = t;
//		a = element_forw(a);
//	}
//	return (array);
// }
