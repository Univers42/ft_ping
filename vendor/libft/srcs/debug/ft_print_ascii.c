/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:48:55 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/10/21 18:59:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stddef.h"
#include "ft_stdio.h"
#include <stdio.h>

void	ft_print_ascii(unsigned char *p, unsigned int size)
{
	unsigned int	j;

	j = 0;
	ft_putchar_fd(' ', STDOUT_FILENO);
	while (j < 16 && j < size)
	{
		if (p[j] >= 32 && p[j] <= 126)
			ft_putchar_fd(p[j], STDOUT_FILENO);
		else
			ft_putchar_fd('.', STDOUT_FILENO);
		j++;
	}
}

//int main(void)
//{
//    unsigned char buffer[20] = {
//        'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l',
// 'd', '!', 0x0A, 0x00, 0x7F, 0x20, 0x41, 0x42, 0x43
//    };
//
//   	ft_printf("ASCII output: ");
//    ft_print_ascii(buffer, 20);
//   	ft_printf("\n");
//
//    return 0;
//}
