/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:43:18 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:34:54 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include "output.h"
#include <stddef.h>

void	flush_all(void)
{
	t_out_ctx	*ctx;

	ctx = get_outs();
	if (!ctx)
		return ;
	flushout(&ctx->output);
	flushout(&ctx->errout);
	flushout(&ctx->prev_err_out);
	flushout(&ctx->memout);
}

void	flushout(t_out *dst)
{
	size_t	len;

	if (dst == NULL || dst->buf == NULL || dst->nextc == NULL)
		return ;
	if (dst->nextc <= dst->buf || dst->fd < 0)
		return ;
	len = (size_t)(dst->nextc - dst->buf);
	if (len == 0)
		return ;
	dst->nextc = dst->buf;
	if (ft_write(dst->fd, dst->buf, len) != 0)
		dst->flags |= OUTPUT_ERR;
}
