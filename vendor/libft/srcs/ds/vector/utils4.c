/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:49:46 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:51:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static ssize_t	read_and_push_chunks(int fd, t_vec *ret)
{
	char	buf[1024];
	ssize_t	n;

	if (!ret)
		return (-1);
	while (1)
	{
		n = read(fd, buf, sizeof(buf));
		if (n == 0)
			break ;
		if (n > 0)
		{
			vec_npush(ret, buf, (size_t)n);
			continue ;
		}
		if (errno == EINTR)
			continue ;
		(perror("read"), exit(1));
	}
	return (0);
}

static void	finalize_null_terminate(t_vec *ret)
{
	if (ret->ctx && ret->elem_size == 1)
	{
		if (!vec_ensure_space_n(ret, 1))
			return ;
		((char *)ret->ctx)[ret->len] = '\0';
	}
}

/* append all data read from fd into a byte-oriented vector (elem_size==1) */
void	vec_append_fd(int fd, t_vec *ret)
{
	if (!ret)
		return ;
	(void)read_and_push_chunks(fd, ret);
	finalize_null_terminate(ret);
}
