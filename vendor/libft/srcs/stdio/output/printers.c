/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:38:31 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:29:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

/**
 * awaiting ft_sprintf ft_snprintf version custom of macro_printf
 * to debug more efficiently
 */
int	ft_fdprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_vfdprintf(fd, str, args);
	va_end(args);
	return (ret);
}

char	*ft_aseprintf(const char *str, ...)
{
	va_list	args;
	char	*ret;

	va_start(args, str);
	ret = ft_vaseprintf(str, args);
	va_end(args);
	return (ret);
}

char	*ft_asprintf(const char *str, ...)
{
	va_list	args;
	char	*ret;

	va_start(args, str);
	ret = ft_vasprintf(str, args);
	va_end(args);
	return (ret);
}

int	ft_eprintf(const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_veprintf(str, args);
	va_end(args);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_vprintf(str, args);
	va_end(args);
	return (ret);
}
