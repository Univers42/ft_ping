/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/05 02:17:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
#include "ft_math.h"

int	find_min_index(t_stck *stack)
{
	int	min;
	int	idx;
	int	i;

	if (!stack || !stack->data || stack->size <= 0)
		return (-1);
	min = stack->data[0];
	idx = 0;
	i = 1;
	while (i < stack->size)
	{
		if (stack->data[i] < min)
		{
			min = stack->data[i];
			idx = i;
		}
		i++;
	}
	return (idx);
}

int	cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}
