/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:52:18 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:23:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

void	print_spec(va_list args, t_fmt_spec spec, t_buffer *buff)
{
	if (spec.t == FMT_NORMAL_CHAR)
		writer_char(buff, spec.data);
	if (spec.t == FMT_PERCENT)
		writer_char(buff, '%');
	printf_char(args, spec, buff);
	printf_string(args, spec, buff);
	printf_int(args, spec, buff);
	printf_unsigned(args, spec, buff);
	printf_hex_lowcase(args, spec, buff);
	printf_hex_upcase(args, spec, buff);
	printf_ptr(args, spec, buff);
}
