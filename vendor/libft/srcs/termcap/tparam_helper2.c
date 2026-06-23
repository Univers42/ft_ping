/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tparam_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:05:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

/* helpers extracted from the original process_format to keep each small */
void	pf_handle_numeric(t_tparam_ctx *ctx, int c, int tem)
{
	int	w;

	if (c == 'd')
		w = 1;
	else
		w = c - '0';
	out_dec_width(&ctx->op, tem, w);
	ctx->args++;
}

void	pf_handle_dot(t_tparam_ctx *ctx, int tem)
{
	append_char(&ctx->op, (char)tem);
	ctx->args++;
}

void	pf_handle_plus(t_tparam_ctx *ctx, int tem)
{
	append_char(&ctx->op, (char)(tem + *ctx->fmt));
	ctx->fmt++;
	ctx->args++;
}

void	pf_handle_gt(t_tparam_ctx *ctx)
{
	if (ctx->args[0] > *ctx->fmt)
		ctx->args[0] += ctx->fmt[1];
	ctx->fmt += 2;
}

void	pf_handle_b(t_tparam_ctx *ctx, int tem)
{
	ctx->args[0] += 6 * (tem / 10);
}
