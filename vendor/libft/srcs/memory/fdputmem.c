/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdputmem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:57:21 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 15:53:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include "ft_string.h"

void	ft_fdputmem(int fd, char *s, int n)
{
	int	i;
	int	written;

	written = 0;
	while (written < n)
	{
		i = write(fd, s + written, n - written);
		if (i < 0)
			break ;
		written += i;
	}
}

void	ft_fdputstr(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	ft_fdputmem(fd, s, i);
}

void	ft_putmem(char *s, int n)
{
	ft_fdputmem(1, s, n);
}

void	ft_eputmem(char *s, int n)
{
	ft_fdputmem(2, s, n);
}
