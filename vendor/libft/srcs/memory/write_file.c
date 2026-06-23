/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:44:09 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 20:31:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_string.h"
#include "ft_stdio.h"

int	write_file_buf(const char *buf, size_t len, int fd)
{
	size_t	total;
	ssize_t	w;

	total = 0;
	if (fd < 0 || !buf)
		return (-1);
	while (total < len)
	{
		w = write(fd, buf + total, len - total);
		if (w < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		if (w == 0)
			break ;
		total += (size_t)w;
	}
	if (total == len)
		return (0);
	return (-1);
}

/* Legacy wrapper for NUL-terminated strings */
int	write_file(const char *str, int fd)
{
	if (!str)
		return (-1);
	return (write_file_buf(str, ft_strlen(str), fd));
}

int	write_to_file(char *str, int fd)
{
	int	wrote_total;
	int	wrote;
	int	len;

	len = ft_strlen(str);
	wrote_total = 0;
	while (wrote_total != len)
	{
		wrote = write(fd, str + wrote_total,
				len - wrote_total);
		if (wrote < 0)
			return (1);
		wrote_total += wrote;
	}
	return (0);
}
