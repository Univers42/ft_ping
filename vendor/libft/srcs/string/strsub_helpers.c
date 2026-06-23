/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsub_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:53:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 14:02:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strsub.h"
#include "ft_memory.h"

int	append_rep(t_subctx *ctx, const char *rep);
int	append_rest(t_subctx *ctx, const char *string, size_t idx);
int	append_char(t_subctx *ctx, char ch);

char	*ensure_capacity(t_subctx *c, size_t need)
{
	size_t	n;

	if (c->tempsize)
		n = c->tempsize * 2;
	else
		n = 16;
	while (n < need)
		n *= 2;
	c->temp = xfn_realloc(c->temp, c->tempsize, n);
	c->tempsize = n;
	return (c->temp);
}

int	handle_match(t_subctx *ctx, const char *string,
						const char *rep, bool glob)
{
	if (append_rep(ctx, rep) < 0)
		return (-1);
	if (ctx->patlen)
		ctx->i += ctx->patlen;
	else
		ctx->i += 1;
	if (!glob)
	{
		if (append_rest(ctx, string, ctx->i) < 0)
			return (-1);
		return (1);
	}
	return (0);
}

char	*finalize_result(t_subctx *ctx, const char *string)
{
	if (ctx->temp)
	{
		ctx->temp[ctx->templen] = '\0';
		return (ctx->temp);
	}
	return (ft_strdup(string));
}
