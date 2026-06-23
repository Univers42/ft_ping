/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outmem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:33:45 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:34:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

static int	try_copy_to_buffer(const char *p, size_t len, t_out *dst)
{
	size_t	n_left;

	n_left = dst->end - dst->nextc;
	if (n_left >= len)
	{
		ft_memcpy(dst->nextc, p, len);
		dst->nextc += len;
		return (1);
	}
	return (0);
}

static void	ensure_buffer_alloc(t_out *dst)
{
	size_t	buf_size;
	size_t	offset;

	buf_size = dst->buf_size;
	if (buf_size != 0 && dst->buf == NULL)
	{
		offset = 0;
		dst->buf = xfn_realloc(dst->buf, 0, buf_size);
		dst->buf_size = buf_size;
		dst->end = dst->buf + buf_size;
		dst->nextc = dst->buf + offset;
	}
	else if (dst->buf != NULL)
		flushout(dst);
}

static void	write_fallback(const char *p, size_t len, t_out *dst)
{
	if (ft_write(dst->fd, p, len))
		dst->flags |= OUTPUT_ERR;
}

void	outmem(const char *p, size_t len, t_out *dst)
{
	if (try_copy_to_buffer(p, len, dst))
		return ;
	ensure_buffer_alloc(dst);
	if (try_copy_to_buffer(p, len, dst))
		return ;
	write_fallback(p, len, dst);
}
