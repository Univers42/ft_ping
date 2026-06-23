/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 03:30:26 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 21:03:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "ft_memory.h"

t_pipe_fds	*pipe_create(void)
{
	int			fds[2];
	t_pipe_fds	*p;

	if (pipe(fds) < 0)
		return (NULL);
	p = (t_pipe_fds *)fn_malloc(sizeof(t_pipe_fds));
	if (!p)
	{
		close(fds[0]);
		close(fds[1]);
		return (NULL);
	}
	p->r = fds[0];
	p->w = fds[1];
	return (p);
}
