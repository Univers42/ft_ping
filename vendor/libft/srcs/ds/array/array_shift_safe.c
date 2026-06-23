/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_shift_safe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:23:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:25:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

t_arr_elem	**array_shift_safe(t_arr *a, int n, int flags)
{
	t_arr_elem	**ret;
	int			i;
	t_arr_elem	*first;

	(void)flags;
	if (a == NULL || array_empty(a) || n <= 0)
		return (NULL);
	ret = (t_arr_elem **)fn_malloc((n + 1) * sizeof(t_arr_elem *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		first = as_get_first_elem(a);
		if (first == NULL || first == a->head)
			break ;
		ret[i] = array_remove(a, element_index(first));
		if (ret[i] == NULL)
			break ;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
