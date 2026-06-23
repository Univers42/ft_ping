/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_copy_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:03:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:28:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "ft_string.h"

t_arr_elem	*array_copy_element(t_arr_elem *ae)
{
	if (ae)
	{
		if (element_value(ae))
			return (array_create_element(element_index(ae),
					ft_strdup(element_value(ae))));
		return (array_create_element(element_index(ae), NULL));
	}
	return (NULL);
}
