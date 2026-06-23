/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:12:38 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/23 16:00:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algebra.h"
#include <stdlib.h>

int	ft_min(int a, int b)
{
	int	diff;
	int	mask;

	diff = ft_subtract(a, b);
	mask = diff >> (sizeof(int) * 8 - 1);
	return ((b & ~mask) | (a & mask));
}

size_t	ft_min2(size_t a, size_t b)
{
	return ((a > b) * b + (a <= b) * a);
}

//
//int main(int argc, char **argv)
//{
//    if (argc != 3)
//        return 1;
//    int a = atoi(argv[1]);
//    int b = atoi(argv[2]);
//   	ft_printf("min(%d, %d) = %d\n", a, b, ft_min(a, b));
//    return 0;
//}
