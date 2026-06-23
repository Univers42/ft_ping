/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:28:55 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:43:52 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H

# include <stdio.h>
# include <sys/types.h>
# include <stdarg.h>
# include "../output/output.h"
# include "../../../include/ft_memory.h"
# include "../../../include/ft_stdlib.h"
# include "../../../include/ft_string.h"

typedef enum e_fmt_spec_type
{
	FMT_UNDEFINED,
	FMT_NORMAL_CHAR,
	FMT_CHAR, // %c
	FMT_STRING, // %s
	FMT_POINTER, // %p
	FMT_INTEGER, // %d, %i
	FMT_UNSIGNED, // %u
	FMT_HEX_LOWER, // %x
	FMT_HEX_UPPER, // %X
	FMT_PERCENT, // %%
}	t_fmt_spec_type;
//cspdiuxX%

typedef enum e_claptrap
{
	CLAP_PRINT = 1 << 0,
	CLAP_ERROR = 1 << 8,
	CLAP_WARNING = 1 << 2,
	CLAP_INFO = 1 << 3,
	CLAP_SUCCESS = 1 << 4,
}	t_claptrap;
typedef enum e_flags
{
	FL_NONE		= 0,
	FL_POUND	= 1, // '#', adds 0x or 0X
	FL_SPACE	= 2, // ' ' adds a whitespace in case num is > 0
	FL_PLUS		= 4, // '+' always add a sign
	FL_MINUS	= 8, // '-' left-justify
	FL_ZERO		= 16, //'0' pad nums with zeros when .width is specified
}	t_flags;

typedef struct s_format_spec
{
	t_fmt_spec_type	t;
	int				flags;
	int				precision;
	int				width;
	char			data;
}	t_fmt_spec;

typedef struct s_buffer
{
	char	*buff;
	int		cap;
	int		len;
	int		total_put_in;
	int		no_write;
	int		out_fd;
}	t_buffer;

// vector of format functions

int			ft_veprintf(const char *str, va_list args);
char		*ft_vaseprintf(const char *str, va_list args);
int			ft_vfdprintf(int fd, const char *str, va_list args);
char		*ft_vasprintf(const char *str, va_list args);
int			ft_vprintf(const char *str, va_list args);

//motor
int			hex_digits(size_t n);
int			hex_padding_len(size_t n, t_fmt_spec spec);
int			hex_total_len(size_t n, t_fmt_spec spec);
t_fmt_spec	normalize_hex_spec(t_fmt_spec spec, size_t n);
int			parse_specifier_param(const char *s, int *i, va_list args);
t_fmt_spec	parse(const char *s, int *i, va_list args);
void		print_spec(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_hex_lowcase(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_hex_upcase(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_int(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_unsigned(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_ptr(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_string(va_list args, t_fmt_spec spec, t_buffer *buff);
void		printf_char(va_list args, t_fmt_spec spec, t_buffer *buff);
int			ptr_total_len(size_t n, t_fmt_spec spec);
t_fmt_spec	normalize_ptr_spec(t_fmt_spec spec);
int			signed_num_digits(ssize_t n);
int			signed_padding_len(ssize_t n, t_fmt_spec spec);
int			signed_total_len(ssize_t n, t_fmt_spec spec);
t_fmt_spec	normilize_int_spec(t_fmt_spec spec, ssize_t i);
int			writer_buffer_double(t_buffer *ret);
void		writer_padn(t_buffer *buff, char padding, int n);
void		writer_char(t_buffer *buffer, char c);
void		writer_strn(t_buffer *buff, char *str, int n);
void		writer_signed(t_buffer *buff, ssize_t n,
				int add_sign, int digits);
void		writer_hex_lowcase(t_buffer *buff, size_t n,
				int add_prefix, int digits);
void		writer_hex_upcase(t_buffer *buff, size_t n,
				int add_prefix, int digits);
int			writer_init(t_buffer *ret);
int			ft_vsnprintf(char *buf, size_t size, const char *str, va_list args);
int			ft_vsprintf(char *buf, const char *str, va_list args);

#endif
