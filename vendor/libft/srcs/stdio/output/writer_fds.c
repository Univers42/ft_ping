/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:33:21 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:29:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "output.h"

void	ft_putchar_fd(char c, int fd)
{
	int	size;

	size = write(fd, &c, 1);
	(void)size;
}

void	ft_putstr_fd(const char *s, int fd)
{
	int	size;

	if (s)
		size = write(fd, s, ft_strlen(s));
	(void)size;
}

void	ft_putnbr_fd(int nb, int fd)
{
	char	digit;
	int		size;

	if (nb == -2147483648)
	{
		size = write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		size = write(fd, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	digit = (nb % 10) + '0';
	size = write(fd, &digit, 1);
	(void)size;
}

void	ft_putnbr_base(int nbr, char *radix)
{
	int		base;
	char	c;
	int		size;

	base = 0;
	while (radix[base])
		base++;
	if (base < 2 || base > 16)
		return ;
	if (nbr < 0)
	{
		size = write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= base)
		ft_putnbr_base(nbr / base, radix);
	c = radix[nbr % base];
	size = write(1, &c, 1);
	(void)size;
}

void	ft_putendl_fd(const char *s, int fd)
{
	int	size;

	if (s)
	{
		size = write(fd, s, ft_strlen(s));
		size += write(fd, "\n", 1);
	}
	(void)size;
}
