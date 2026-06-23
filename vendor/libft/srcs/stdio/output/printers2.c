/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:17:34 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:17:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include <stdlib.h>

int	ft_snprintf(char *buf, size_t size, const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_vsnprintf(buf, size, str, args);
	va_end(args);
	return (ret);
}

int	ft_sprintf(char *buf, const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_vsprintf(buf, str, args);
	va_end(args);
	return (ret);
}
