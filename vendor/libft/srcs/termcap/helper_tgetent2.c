/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_tgetent2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:49:55 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:38:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

/* copy from src to dest pointer, removing backslash-newline continuations */
static void	copy_strip_backslash(char **dest, char **src)
{
	int	c;

	while (1)
	{
		c = *(*src)++;
		*(*dest)++ = c;
		if (c == '\0' || c == '\n')
			break ;
		if (c == '\\' && **src == '\n')
		{
			(*dest)--;
			(*src)++;
		}
	}
	*(*dest) = '\0';
}

/* ensure ctx->bp has enough capacity when ctx->malloc_size is set */
static void	ensure_ctx_capacity(t_tgetent_ctx *ctx, t_buf *buf)
{
	const size_t	old_size = ctx->malloc_size;
	char			*tmp;

	ctx->malloc_size = ctx->bp1 - ctx->bp + buf->size;
	tmp = (char *)xfn_realloc(ctx->bp, old_size, ctx->malloc_size);
	ctx->bp1 += tmp - ctx->bp;
	ctx->bp = tmp;
}

/* write current buffer line into ctx and return pointer to line start */
static char	*write_entry_line(t_tgetent_ctx *ctx, t_buf *buf)
{
	char	*bp2;
	char	*tmp;

	bp2 = ctx->bp1;
	tmp = buf->ptr;
	copy_strip_backslash(&ctx->bp1, &tmp);
	return (bp2);
}

/* obtain next term from a stored entry's tc= capability */
static char	*next_term_from_entry(char *entry_start)
{
	return (tgetst1(find_capability(entry_start, "tc"), NULL));
}

/* read database entries and follow tc= indirections */
int	process_entries(t_tgetent_ctx *ctx, char *name, t_buf *buf, int fd)
{
	char	*term;
	char	*bp2;

	if (ctx->indirect)
		term = ctx->indirect;
	else
		term = name;
	while (term)
	{
		if (scan_file(term, fd, buf) == 0)
			return (0);
		if (term != name)
			fn_free(term);
		if (ctx->malloc_size)
			ensure_ctx_capacity(ctx, buf);
		bp2 = write_entry_line(ctx, buf);
		term = next_term_from_entry(bp2);
	}
	return (1);
}
