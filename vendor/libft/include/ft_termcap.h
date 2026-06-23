/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 00:49:54 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:09:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMCAP_H
# define FT_TERMCAP_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stdio.h>
# include "ft_memory.h"
# include "ft_string.h"
# include "ft_stdio.h"

typedef struct s_buf
{
	char	*beg;
	char	*ptr;
	int		size;
	int		ateof;
	int		full;
}	t_buf;

typedef struct s_tgetent_ctx
{
	char	*bp;
	char	*bp1;
	int		malloc_size;
	char	*indirect;
	char	*tcenv;
}	t_tgetent_ctx;

typedef struct s_tglob
{
	char		pc;
	short		ospeed;
	int			*speeds;
	char		*up;
	char		*bc;
	int			tputs_baud_rate;
	char		*esctab;
	char		*term_entry;
	int			used_fallback;
}	t_tglob;

typedef struct s_tparam_ctx
{
	const char	*fmt;
	char		*op;
	int			*args;
	int			cap;
	char		*buf;
}	t_tparam_ctx;

t_tglob		*access_glob(void);
int			tgetent(char *bp, const char *name);
char		*tgetst1(char *ptr, char **area);
char		*tparam(const char *fmt, char *out, int size, int *args);
/* newly added public prototypes */
char		*tgetstr(const char *cap, char **area);
int			tgetnum(const char *cap);
int			tgetflag(const char *cap);
int			tputs(const char *str, int nlines, int (*outfn)(int));
char		*tgoto(const char *cm, int hpos, int vpos);
int			tc_atoi(const char *s);
/* helper functions */
char		*find_capability(char *bp, char *cap);
int			scan_file(char *str, int fd, t_buf *bufp);
char		*gobble_line(int fd, t_buf *b, char *ae);
/* tparam helpers and utilities (prototypes for other translation units) */
int			pf_step1(t_tparam_ctx *ctx, int c, int tem);
int			pf_step2(t_tparam_ctx *ctx, int c);
int			pf_step3(t_tparam_ctx *ctx, int c, int tem);
void		pf_handle_unknown(t_tparam_ctx *ctx, int c);
char		*grow(char *base, char **op, int *cap);
void		append_char(char **op, char c);
/* additional helpers used across tparam units */
void		out_dec_width(char **op, int v, int w);
void		op_swap(int *a, int *b);
void		op_arith(int *a0, const char **fmt, int *args);
/* handlers implemented in helper files */
void		pf_handle_numeric(t_tparam_ctx *ctx, int c, int tem);
void		pf_handle_dot(t_tparam_ctx *ctx, int tem);
void		pf_handle_plus(t_tparam_ctx *ctx, int tem);
void		pf_handle_gt(t_tparam_ctx *ctx);
void		pf_handle_b(t_tparam_ctx *ctx, int tem);
void		pf_handle_d(t_tparam_ctx *ctx, int tem);
void		pf_handle_c(t_tparam_ctx *ctx, int tem);
/* terminal helpers (small wrappers over termcap strings) */
int			tc_get_size(int *rows, int *cols);
void		tc_clear_screen(void);
void		tc_clear_eol(void);
void		tc_move_cursor(int row, int col); /* 0-based */
void		tc_save_cursor(void);
void		tc_restore_cursor(void);
void		tc_enter_bold(void);
void		tc_exit_attr(void);
/* readline-like helper: minimal line editor using termcap */
char		*rl_getline(const char *prompt);
int			termcap_used_fallback(void);
void		termcap_mark_fallback(void);

#endif
