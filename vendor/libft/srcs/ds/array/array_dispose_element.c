/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_dispose_element.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:02:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 13:54:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	array_dispose_element(t_arr_elem *ae)
{
	if (ae)
	{
		fn_free(ae->val);
		fn_free(ae);
	}
}
