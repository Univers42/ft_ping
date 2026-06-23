/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:59:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void	array_pop(t_arr *a)
{
	char	*val;

	if (a == NULL || array_empty(a))
		return ;
	if (array_shift(a, &val) == 0)
		fn_free(val);
}
