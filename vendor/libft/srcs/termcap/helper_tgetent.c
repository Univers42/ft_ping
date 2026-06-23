/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tgetent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:44:50 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 13:15:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"
#include "ft_string.h"

void	copy_env_direct_to_ctx(t_tgetent_ctx *ctx, char *bp, char *termcap_name)
{
	if (bp)
		ft_strcpy(bp, termcap_name);
	else
	{
		ctx->malloc_size = (int)(ft_strlen(termcap_name) + 1);
		ctx->bp = (char *)fn_malloc(ctx->malloc_size);
		ft_strcpy(ctx->bp, termcap_name);
	}
	ctx->tcenv = termcap_name;
}

/* condensed env handling; returns:
   - NULL when we set ctx->tcenv (inline entry) or when tc= processed (indirect),
   - non-NULL string when TERMCAP env gives a path (starts with '/'),
   - NULL when TERMCAP not set (preserve original semantics). */
char	*handle_env_direct(char *name, char *bp, t_tgetent_ctx *ctx)
{
	char	*termcap_name;
	char	*term_env;

	termcap_name = getenv("TERMCAP");
	if (termcap_name && *termcap_name == '\0')
		termcap_name = NULL;
	if (!termcap_name || *termcap_name == '/')
		return (termcap_name);
	term_env = getenv("TERM");
	if (!term_env || strcmp(name, term_env) != 0)
		return (termcap_name);
	ctx->indirect = tgetst1(find_capability(termcap_name, "tc"), NULL);
	if (!ctx->indirect)
	{
		copy_env_direct_to_ctx(ctx, bp, termcap_name);
		return (NULL);
	}
	ctx->tcenv = termcap_name;
	return (NULL);
}

/* copy a line from src to bp1, removing backslash-newline continuations */
void	copy_line_strip_backslash(char **bp1, char **src)
{
	int	c;

	while (1)
	{
		c = *(*src)++;
		*(*bp1)++ = c;
		if (c == '\0' || c == '\n')
			break ;
		if (c == '\\' && **src == '\n')
		{
			(*bp1)--;
			(*src)++;
		}
	}
	*(*bp1) = '\0';
}

/* init internal buffers used to assemble term entry */
int	init_buffers(t_tgetent_ctx *ctx, t_buf *buf)
{
	if (!ctx->bp)
	{
		if (ctx->indirect)
			ctx->malloc_size = (int)(ft_strlen(ctx->tcenv) + 1);
		else
			ctx->malloc_size = buf->size;
		ctx->bp = (char *)fn_malloc(ctx->malloc_size);
	}
	ctx->bp1 = ctx->bp;
	if (ctx->indirect)
	{
		ft_strcpy(ctx->bp, ctx->tcenv);
		ctx->bp1 += ft_strlen(ctx->tcenv);
	}
	return (1);
}
