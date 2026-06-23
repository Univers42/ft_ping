/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tparam_steps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:06:33 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

/* step helpers to keep process_format under 25 lines */
int	pf_step1(t_tparam_ctx *ctx, int c, int tem)
{
	if (c == 'd' || c == '2' || c == '3')
		return (pf_handle_numeric(ctx, c, tem), 1);
	if (c == '.')
		return (pf_handle_dot(ctx, tem), 1);
	if (c == '+')
		return (pf_handle_plus(ctx, tem), 1);
	if (c == 'i')
	{
		ctx->args[0]++;
		ctx->args[1]++;
		return (1);
	}
	return (0);
}

int	pf_step2(t_tparam_ctx *ctx, int c)
{
	if (c == 'r')
		return (op_swap(&ctx->args[0], &ctx->args[1]), 1);
	if (c == 'f')
	{
		ctx->args++;
		return (1);
	}
	if (c == 'b')
	{
		ctx->args--;
		return (1);
	}
	if (c == '>')
		return (pf_handle_gt(ctx), 1);
	return (0);
}

int	pf_step3(t_tparam_ctx *ctx, int c, int tem)
{
	if (c == 'a')
		return (op_arith(&ctx->args[0], &ctx->fmt, ctx->args), 1);
	if (c == 'n')
	{
		ctx->args[0] ^= 0140;
		ctx->args[1] ^= 0140;
		return (1);
	}
	if (c == 'm')
	{
		ctx->args[0] ^= 0177;
		ctx->args[1] ^= 0177;
		return (1);
	}
	if (c == 'B')
		return (pf_handle_b(ctx, tem), 1);
	if (c == 'D')
		return (pf_handle_d(ctx, tem), 1);
	if (c == 'C')
		return (pf_handle_c(ctx, tem), 1);
	return (0);
}
