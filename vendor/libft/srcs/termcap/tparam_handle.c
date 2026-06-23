/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tparam_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:07:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

void	pf_handle_d(t_tparam_ctx *ctx, int tem)
{
	ctx->args[0] -= 2 * (tem % 16);
}

void	pf_handle_c(t_tparam_ctx *ctx, int tem)
{
	if (tem >= 96)
		append_char(&ctx->op, (char)(tem / 96));
	append_char(&ctx->op, (char)(tem + *ctx->fmt));
	ctx->fmt++;
	ctx->args++;
}

void	pf_handle_unknown(t_tparam_ctx *ctx, int c)
{
	append_char(&ctx->op, '%');
	append_char(&ctx->op, (char)c);
}
