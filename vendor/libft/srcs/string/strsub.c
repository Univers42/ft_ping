/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:58:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/05 02:16:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strsub.h"

char	*strsub(const char *string, const char *pat,
			const char *rep, bool glob)
{
	t_subctx	ctx;
	int			res;

	ctx = (t_subctx){0};
	ctx.patlen = ft_strlen(pat);
	while (string[ctx.i])
	{
		if (ctx.patlen && ft_strncmp(string + ctx.i, pat, ctx.patlen) == 0)
		{
			res = handle_match(&ctx, string, rep, glob);
			if (res < 0)
				return (NULL);
			if (res > 0)
				break ;
		}
		else
		{
			if (append_char(&ctx, string[ctx.i]) < 0)
				return (NULL);
			ctx.i++;
		}
	}
	return (finalize_result(&ctx, string));
}

/* append replacement string 'rep' into ctx->temp */
int	append_rep(t_subctx *ctx, const char *rep)
{
	ctx->repn = ft_strlen(rep);
	if (!ensure_capacity(ctx, ctx->templen + ctx->repn + 1))
		return (-1);
	if (ctx->repn)
	{
		ft_strncpy(ctx->temp + ctx->templen, rep, ctx->repn);
		ctx->templen += ctx->repn;
	}
	return (0);
}

/* append remaining part of original string starting at idx */
int	append_rest(t_subctx *ctx, const char *string, size_t idx)
{
	ctx->remn = ft_strlen(string + idx);
	if (!ensure_capacity(ctx, ctx->templen + ctx->remn + 1))
		return (-1);
	if (ctx->remn)
	{
		ft_strncpy(ctx->temp + ctx->templen, string + idx, ctx->remn);
		ctx->templen += ctx->remn;
	}
	return (0);
}

/* append single character ch to buffer */
int	append_c(t_subctx *ctx, char ch)
{
	if (!ensure_capacity(ctx, ctx->templen + 2))
		return (-1);
	ctx->temp[ctx->templen++] = ch;
	return (0);
}
