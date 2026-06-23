/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:29:18 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 15:53:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "../format/format.h"
# include <unistd.h>
# include <stdarg.h>
# include "../../../include/ft_string.h"
# include "../../../include/ft_memory.h"

typedef struct s_state_fd	t_state_fd;

# define OUTPUT_ERR 01
# define OUTBUFSIZE 1024

typedef struct s_clap_state
{
	char	*accum;
	size_t	accum_len;
	int		has_error;
}	t_clap_state;

typedef struct s_out
{
	char	*nextc;
	char	*end;
	char	*buf;
	size_t	buf_size;
	int		fd;
	int		flags;
}	t_out;

typedef struct s_out_ctx
{
	t_out	output;
	t_out	prev_err_out;
	t_out	errout;
	t_out	memout;
	t_out	*out1;
	t_out	*out2;
}	t_out_ctx;

typedef struct s_fdio
{
	int				fd;
	int				flags;
	char			*io_read_ptr;
	char			*io_read_end;
	char			*io_read_base;
	char			*io_write_base;
	char			*io_write_ptr;
	char			*io_write_end;
	char			*io_buf_base;
	char			*io_buf_end;
	char			*io_save_base;
	char			*io_bak;
	char			*save_end;
	struct s_file	*chain;
	int				flags2;
	unsigned short	cur_column;
	signed char		vable_offset;
	char			short_buf[1];
	void			*lock;
}	t_fdio;

static inline t_out_ctx	*get_outs(void)
{
	static t_out_ctx	ctx;
	static int			inited = 0;

	if (inited)
		return (&ctx);
	ctx.output.buf_size = OUTBUFSIZE;
	ctx.output.fd = STDOUT_FILENO;
	ctx.prev_err_out.buf_size = OUTBUFSIZE;
	ctx.prev_err_out.fd = STDERR_FILENO;
	ctx.errout.buf_size = OUTBUFSIZE;
	ctx.errout.fd = STDERR_FILENO;
	ctx.memout.buf_size = OUTBUFSIZE;
	ctx.memout.fd = STDOUT_FILENO;
	ctx.out1 = &ctx.output;
	ctx.out2 = &ctx.errout;
	inited = 1;
	return (&ctx);
}

t_clap_state	*get_clap_state(void);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_base(int nbr, char *radix);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			outmem(const char *p, size_t len, t_out *dst);
void			flushout(t_out *dst);
int				ft_write(int fd, const void *p, size_t n);
void			flush_all(void);
char			*ft_asprintf(const char *str, ...);
int				ft_fdprintf(int fd, const char *str, ...);
char			*ft_aseprintf(const char *str, ...);
int				ft_eprintf(const char *str, ...);
int				ft_printf(const char *str, ...);
void			ft_putmem(char *s, int n);
void			ft_eputmem(char *s, int n);
void			ft_fdputmem(int fd, char *s, int n);
int				ft_sprintf(char *buf, const char *str, ...);
int				ft_snprintf(char *buf, size_t size, const char *str, ...);
int				claptrap(int flag, const char *str, ...);
const char		*select_prefix(int flag);
char			*build_formatted_msg(const char *prefix,
							const char *msg,
							size_t *out_len);
int				append_accum(char *formatted, size_t new_len);
void			flush_accum(void);

#endif