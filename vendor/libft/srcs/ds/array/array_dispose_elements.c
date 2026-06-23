/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_dispose_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:55:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:55:33 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

/*
 * Dispose a NULL-terminated array of t_arr_elem pointers.
 * Each element is disposed via array_dispose_element and the container is freed.
 */
void	array_dispose_elements(t_arr_elem **elements)
{
	t_arr_elem	**it;

	if (elements == NULL)
		return ;
	it = elements;
	while (*it != NULL)
	{
		array_dispose_element(*it);
		it++;
	}
	fn_free(elements);
}
