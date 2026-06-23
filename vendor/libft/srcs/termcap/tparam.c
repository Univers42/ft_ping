/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tparam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 00:50:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 22:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

/* short delegator: reads the code and dispatches to small steps */
static void	process_format(t_tparam_ctx *ctx)
{
	int	c;
	int	tem;

	c = *ctx->fmt;
	ctx->fmt++;
	tem = *ctx->args;
	if (pf_step1(ctx, c, tem))
		return ;
	if (pf_step2(ctx, c))
		return ;
	if (pf_step3(ctx, c, tem))
		return ;
	pf_handle_unknown(ctx, c);
}

static void	process_tparam_loop(t_tparam_ctx *ctx)
{
	while (*ctx->fmt)
	{
		if (ctx->op - ctx->buf + 8 >= ctx->cap)
			ctx->buf = grow(ctx->buf, &ctx->op, &ctx->cap);
		if (*ctx->fmt != '%')
		{
			append_char(&ctx->op, *ctx->fmt++);
			continue ;
		}
		ctx->fmt++;
		if (*ctx->fmt == '%')
		{
			append_char(&ctx->op, '%');
			ctx->fmt++;
			continue ;
		}
		process_format(ctx);
	}
	*ctx->op = '\0';
}

char	*tparam(const char *fmt, char *out, int size, int *args)
{
	t_tparam_ctx	ctx;

	if (!fmt)
		return (NULL);
	ctx.fmt = fmt;
	ctx.args = args;
	ctx.cap = size;
	if (out)
		ctx.buf = out;
	else
		ctx.buf = (char *)fn_malloc(size);
	ctx.op = ctx.buf;
	process_tparam_loop(&ctx);
	return (ctx.buf);
}
