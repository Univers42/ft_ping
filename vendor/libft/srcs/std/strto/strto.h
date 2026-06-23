/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:07:50 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/27 16:16:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTO_H
# define STRTO_H

# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <inttypes.h>
# include <string.h>
# include "../../../include/ft_stddef.h"

// Conversion state machine states
typedef enum e_conv
{
	CONV_STATE_INIT = 0,
	CONV_STATE_WHITESPACE,
	CONV_STATE_SIGN,
	CONV_STATE_BASE_PREFIX,
	CONV_STATE_DIGITS,
	CONV_STATE_OVERFLOW,
	CONV_STATE_DONE,
	CONV_STATE_ERROR
}	t_conv;

// Aliases used in code
# define STATE_INIT CONV_STATE_INIT
# define STATE_WHITESPACE CONV_STATE_WHITESPACE
# define STATE_SIGN CONV_STATE_SIGN
# define STATE_BASE_PREFIX CONV_STATE_BASE_PREFIX
# define STATE_DIGITS CONV_STATE_DIGITS
# define STATE_OVERFLOW CONV_STATE_OVERFLOW
# define STATE_DONE CONV_STATE_DONE
# define STATE_ERROR CONV_STATE_ERROR

// Number of states in the table
# define CONV_STATE_COUNT 8
# define TYPE_INFO_COUNT 18

// Supported target types

// Conversion ctx (state machine data)
typedef struct s_conv_ctx
{
	const char	*ptr;
	const char	*start;
	char		**endptr;
	int			base;
	t_type		type;
	t_type_info	type_info;
	uint64_t	uval;
	bool		negative;
	bool		any_digit;
	t_conv		state;
}	t_conv_ctx;

// Forward-declare ctx for the function pointer type
typedef void	(*t_fn_state)(t_conv_ctx *);

// Backward-compat alias used by callers.
# ifndef TYPE_LONG_LONG
#  define TYPE_LONG_LONG TYPE_LLONG
# endif

// Return the static table pointer
// (fixed: use an array, not a pointer with a struct literal).

# ifdef __cplusplus

static inline const t_type_info	*type_info_table(void)
{
	static const t_type_info	gtable[] = {
	{UCHAR_MAX, 0, false},	/* TYPE_UCHAR */
	{CHAR_MAX, CHAR_MIN, true},		/* TYPE_CHAR */
	{USHRT_MAX, 0, false},			/* TYPE_USHORT */
	{SHRT_MAX, SHRT_MIN, true},		/* TYPE_SHORT */
	{UINT_MAX, 0, false},			/* TYPE_UINT */
	{INT_MAX, INT_MIN, true},		/* TYPE_INT */
	{ULONG_MAX, 0, false},			/* TYPE_ULONG */
	{LONG_MAX, LONG_MIN, true},		/* TYPE_LONG */
	{ULLONG_MAX, 0, false},			/* TYPE_ULLONG */
	{LLONG_MAX, LLONG_MIN, true},	/* TYPE_LLONG */
	{UINT8_MAX, 0, false},			/* TYPE_UINT8 */
	{INT8_MAX, INT8_MIN, true},		/* TYPE_INT8 */
	{UINT16_MAX, 0, false},			/* TYPE_UINT16 */
	{INT16_MAX, INT16_MIN, true},	/* TYPE_INT16 */
	{UINT_MAX, 0, false},			/* TYPE_UINT32 (mapped) */
	{INT_MAX, INT_MIN, true},		/* TYPE_INT32 (mapped) */
	{ULLONG_MAX, 0, false},			/* TYPE_UINT64 (mapped) */
	{LLONG_MAX, LLONG_MIN, true}	/* TYPE_INT64 (mapped) */
	};

	return (gtable);
}
# else

static inline const t_type_info	*type_info_table(void)
{
	static const t_type_info	gtable[] = {
	[TYPE_UCHAR] = {UCHAR_MAX, 0, false},
	[TYPE_CHAR] = {CHAR_MAX, CHAR_MIN, true},
	[TYPE_USHORT] = {USHRT_MAX, 0, false},
	[TYPE_SHORT] = {SHRT_MAX, SHRT_MIN, true},
	[TYPE_UINT] = {UINT_MAX, 0, false},
	[TYPE_INT] = {INT_MAX, INT_MIN, true},
	[TYPE_ULONG] = {ULONG_MAX, 0, false},
	[TYPE_LONG] = {LONG_MAX, LONG_MIN, true},
	[TYPE_ULLONG] = {ULLONG_MAX, 0, false},
	[TYPE_LLONG] = {LLONG_MAX, LLONG_MIN, true},
	[TYPE_UINT8] = {UINT8_MAX, 0, false},
	[TYPE_INT8] = {INT8_MAX, INT8_MIN, true},
	[TYPE_UINT16] = {UINT16_MAX, 0, false},
	[TYPE_INT16] = {INT16_MAX, INT16_MIN, true},
	[TYPE_UINT32] = {UINT_MAX, 0, false},
	[TYPE_INT32] = {INT_MAX, INT_MIN, true},
	[TYPE_UINT64] = {ULLONG_MAX, 0, false},
	[TYPE_INT64] = {LLONG_MAX, LLONG_MIN, true}};

	return (gtable);
}
# endif

int64_t				ft_strto(const char *nptr, char **endptr, int base,
									t_type type);
t_type				get_type_from_size(size_t size, bool is_unsigned);
int8_t				ft_strto_i8(const char *nptr, char **endptr, int base);
uint16_t			ft_strto_u16(const char *nptr, char **endptr, int base);
int16_t				ft_strto_i16(const char *nptr, char **endptr, int base);
uint32_t			ft_strto_u32(const char *nptr, char **endptr, int base);
int32_t				ft_strto_i32(const char *nptr, char **endptr, int base);
unsigned int		ft_strto_uint(const char *nptr, char **endptr, int base);
int					ft_strto_int(const char *nptr, char **endptr, int base);
unsigned long		ft_strto_ulong(const char *nptr, char **endptr, int base);
long				ft_strto_long(const char *nptr, char **endptr, int base);
uint8_t				ft_strto_u8(const char *nptr, char **endptr, int base);
int64_t				ft_strto64(const char *nptr, char **endptr, int base);
unsigned char		ft_strto_uchar(const char *nptr, char **endptr, int base);
signed char			ft_strto_char(const char *nptr, char **endptr, int base);
unsigned short		ft_strto_ushort(const char *nptr, char **endptr, int base);
short				ft_strto_short(const char *nptr, char **endptr, int base);
uint64_t			ft_strtoull(const char *nptr, char **endptr, int base);
int64_t				ft_strtoint(const char *nptr, char **endptr, int base,
									t_type type);
uint64_t			ft_strtou64(const char *nptr, char **endptr, int base);
int64_t				ft_strto_unsigned(const char *nptr, char **endptr, int base,
									size_t size);
int64_t				ft_strto_signed(const char *nptr, char **endptr, int base,
									size_t size);

// Existing state handlers
void				state_whitespace(t_conv_ctx *ctx);
void				state_sign(t_conv_ctx *ctx);
void				state_base_prefix(t_conv_ctx *ctx);
void				state_digits(t_conv_ctx *ctx);
void				state_overflow(t_conv_ctx *ctx);

// Helpers
void				init_conv_ctx(t_conv_ctx *ctx,
									const char *nptr,
									int base,
									t_type type);
int					char_to_digit(char c, int base);
const t_type_info	*get_type_info(t_type type);

static inline const t_fn_state	*conv_state_table(void)
{
	static const t_fn_state	table[CONV_STATE_COUNT] = {
	[STATE_INIT] = NULL,
	[STATE_WHITESPACE] = state_whitespace,
	[STATE_SIGN] = state_sign,
	[STATE_BASE_PREFIX] = state_base_prefix,
	[STATE_DIGITS] = state_digits,
	[STATE_OVERFLOW] = state_overflow,
	[STATE_DONE] = NULL,
	[STATE_ERROR] = NULL};

	return (table);
}

#endif
