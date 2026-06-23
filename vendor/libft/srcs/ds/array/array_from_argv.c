/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_from_argv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:42:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/30 21:03:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// static t_arr *fast_case(t_arr *a, char **vec, int count)
//{
//     ssize_t		i;
//     t_arr_elem	*ae;
//     char		*t;
//
//     if (array_num_elements(a) == count && count == 1)
//     {
//         ae = element_forw(a->head);
//		t = 0;
//		if (vec[0])
//			t = savestring(vec[0]);
//         array_element_replace(ae, t);
//     }
//     else if (array_num_elements(a) <= count)
//     {
//         ae = a->head;
//		i = -1;
//         while (++i < array_num_elements(a))
//         {
//             ae = element_forw(ae);
//			t = 0;
//			if (vec[0])
//				t = savestring(vec[0]);
//             array_element_replace(ae, t);
//         }
//         while (i < count)
//		{
//             array_insert(a, i, vec[i]);
//			i++;
//		}
//     }
//     else
//     {
//     	array_flush(a);
//		i = -1;
//     	while (++i < count)
//			array_insert(a, i, vec[i]);
//     }
//     return (a);
// }
//
// t_arr	*array_from_argv(t_arr *a, char **vec, int count)
//{
//	ssize_t	i;
//
//	if (a == 0 || array_num_elements (a) == 0)
//	{
//		i = -1;
//		while (++i < count)
//			array_insert(a, i, vec[i]);
//		return (a);
//	}
//	return (fast_case(a, vec, count));
// }
