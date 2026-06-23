/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_close_pair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 03:33:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 21:03:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "ft_memory.h"

void	pipe_close_pair(t_pipe_fds *p)
{
	if (!p)
		return ;
	if (p->r >= 0)
	{
		close(p->r);
		p->r = -1;
	}
	if (p->w >= 0)
	{
		close(p->w);
		p->w = -1;
	}
}
