/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_quote_escapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:32:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/30 21:04:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// t_arr *array_quote_escapes(t_arr *array)
// {
// 	t_arr_elem  *ae;
// 	char        *t;

// 	if (array == 0 || array_head(array) == 0 || array_empty(array))
// 		return (t_arr *)NULL;
//     ae = element_forw(array->head);
// 	while (ae != array->head)
//     {
// 		t = quote_escapes(ae->val);
// 		free(ae->val);
// 		ae->val = t;
//         ae = element_forw(ae);
// 	}
// 	return (array);
// }
