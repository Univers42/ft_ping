/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:36:31 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:42:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

void	copy_env_direct_to_ctx(t_tgetent_ctx *ctx, char *bp,
			char *termcap_name);
char	*handle_env_direct(char *name, char *bp, t_tgetent_ctx *ctx);
void	copy_line_strip_backslash(char **bp1, char **src);
int		process_entries(t_tgetent_ctx *ctx, char *name, t_buf *buf,
			int fd);
int		init_buffers(t_tgetent_ctx *ctx, t_buf *buf);
char	*fallback_entry(const char *name);
int		apply_fallback(char *bp, const char *name);
void	init_tgetent_ctx(t_tgetent_ctx *ctx, char *bp);

/* prepare env handling and short-circuit when TERMCAP provided inline */
static int	handle_env_and_prepare(t_tgetent_ctx *ctx, char *bp,
				const char *name, char **termcap_file)
{
	*termcap_file = handle_env_direct((char *)name, bp, ctx);
	if (!*termcap_file && ctx->tcenv && !ctx->indirect && (bp || ctx->bp))
	{
		if (ctx->bp)
			access_glob()->term_entry = ctx->bp;
		else
			access_glob()->term_entry = bp;
		return (1);
	}
	return (0);
}

/* read file and process entries; tries fallback on error */
static int	read_and_process_file(t_tgetent_ctx *ctx, char *bp,
							const char *name, char *termcap_file)
{
	t_buf	buf;
	int		fd;

	fd = open(termcap_file, O_RDONLY, 0);
	if (fd < 0)
	{
		fn_free(ctx->indirect);
		return (apply_fallback(bp, name));
	}
	buf.size = 2048;
	buf.beg = (char *)fn_malloc(buf.size + 1);
	buf.ptr = buf.beg;
	buf.ateof = 0;
	buf.full = 0;
	init_buffers(ctx, &buf);
	if (!process_entries(ctx, (char *)name, &buf, fd))
	{
		close(fd);
		fn_free(buf.beg);
		if (ctx->malloc_size)
			fn_free(ctx->bp);
		return (apply_fallback(bp, name));
	}
	return (close(fd), fn_free(buf.beg), 1);
}

/* finalize: shrink allocated buffer and set global term_entry */
static void	finalize_entry(t_tgetent_ctx *ctx, char *bp)
{
	if (ctx->malloc_size)
		ctx->bp = (char *)xfn_realloc(ctx->bp, ctx->bp1 - ctx->bp,
				ctx->bp1 - ctx->bp + 1);
	if (ctx->bp)
		access_glob()->term_entry = ctx->bp;
	else
		access_glob()->term_entry = bp;
}

/* top-level entry */
int	tgetent(char *bp, const char *name)
{
	t_tgetent_ctx	ctx;
	char			*termcap_file;
	int				result;

	if (bp)
		access_glob()->term_entry = bp;
	init_tgetent_ctx(&ctx, bp);
	if (handle_env_and_prepare(&ctx, bp, name, &termcap_file))
		return (1);
	if (!termcap_file)
		termcap_file = "/etc/termcap";
	result = read_and_process_file(&ctx, bp, name, termcap_file);
	if (result == 1)
		finalize_entry(&ctx, bp);
	return (result);
}
