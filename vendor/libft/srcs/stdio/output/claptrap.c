/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   claptrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:10:50 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 15:01:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include <stdlib.h>

#ifndef VERBOSE

int	claptrap(int flag, const char *str, ...)
{
	va_list		args;
	char		*msg;
	const char	*prefix;
	char		*formatted;
	size_t		new_len;

	if (flag & CLAP_PRINT)
		return (flush_accum(), 0);
	if (flag & CLAP_ERROR)
		get_clap_state()->has_error = 1;
	va_start(args, str);
	msg = ft_vasprintf(str, args);
	va_end(args);
	if (!msg)
		return (0);
	prefix = select_prefix(flag);
	formatted = build_formatted_msg(prefix, msg, &new_len);
	fn_free(msg);
	if (!formatted)
		return (0);
	if (!append_accum(formatted, new_len))
		return (fn_free(formatted), 0);
	return (fn_free(formatted), 1);
}

#else

int	claptrap(int flag, const char *str, ...)
{
	(void)flag;
	(void)str;
	return (1);
}
#endif
