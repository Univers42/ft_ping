/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_qsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:16:18 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 01:49:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qsort.h"

/* recursive quicksort using copies of metas for left/right partitions */
void	qsort_rec(t_intern *metas)
{
	size_t		p;
	t_intern	left;
	t_intern	right;

	if (metas->low >= metas->high)
		return ;
	p = partition(metas);
	if (p > 0)
	{
		left = *metas;
		left.high = p - 1;
		qsort_rec(&left);
	}
	right = *metas;
	right.low = p + 1;
	qsort_rec(&right);
}
