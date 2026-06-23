/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:48:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/30 21:04:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// char **
// array_to_argv (t_arr *a, int *countp)
// {
// 	char		**ret;
// 	char		*t;
// 	int			i;
// 	t_arr_elem	*ae;

// 	if (a == 0 || array_empty(a)) {
// 		if (countp)
// 			*countp = 0;
// 		return ((char **)NULL);
// 	}
// 	ret = strvec_create(array_num_elements (a) + 1);
// 	i = 0;
// 	for (ae = element_forw(a->head); ae != a->head; ae = element_forw(ae))
// 	{
// 		t = element_value (ae);
// 		if (t)
// 			ret[i++] = savestring (t);
// 	}
// 	ret[i] = (char *)NULL;
// 	if (countp)
// 		*countp = i;
// 	return (ret);
// }
