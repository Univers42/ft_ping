/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:41:35 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:28:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>
#include <stdint.h>

/**
 * Wrapper around write that ensure all n bytes are written
 * handling partial writes, signals (EINTR) and very large sizes
 * by chopping into ssize_max sizes chunks returns 0 on success, -1 on error
 */
int	ft_write(int fd, const void *p, size_t n)
{
	const char	*buf = p;
	ssize_t		i;
	size_t		m;

	while (n)
	{
		m = n;
		i = write(fd, buf, m);
		while (i < 0 && errno == EINTR)
			i = write(fd, buf, m);
		if (i < 0)
			return (-1);
		buf += i;
		n -= (size_t)i;
	}
	return (0);
}
