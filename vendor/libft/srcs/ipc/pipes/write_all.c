/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 03:36:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 21:04:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "ft_memory.h"

/* write all bytes (handles EINTR), returns n on success, -1 on error */
ssize_t	write_all(int fd, const void *buf, size_t n)
{
	const char	*ptr = (const char *)buf;
	size_t		left;
	ssize_t		w;

	left = n;
	while (left)
	{
		w = write(fd, ptr, left);
		if (w < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		if (w == 0)
			return ((ssize_t)(n - left));
		left -= (size_t)w;
		ptr += w;
	}
	return ((ssize_t)n);
}
