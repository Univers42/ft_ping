/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 03:37:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 03:57:26 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

/* read up to n bytes (handles EINTR),
returns bytes read (0 on EOF), -1 on error */
ssize_t	read_all(int fd, void *buf, size_t n)
{
	char	*ptr;
	size_t	left;
	ssize_t	r;

	ptr = (char *)buf;
	left = n;
	while (left)
	{
		r = read(fd, ptr, left);
		if (r < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		if (r == 0)
			break ;
		left -= (size_t)r;
		ptr += r;
	}
	return ((ssize_t)(n - left));
}
