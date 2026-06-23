/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprinter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:48:22 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:23:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

int	ft_vprintf(const char *str, va_list args)
{
	int				i;
	t_fmt_spec		spec;
	t_buffer		buff;

	i = 0;
	writer_init(&buff);
	while (str[i])
	{
		spec = parse(str, &i, args);
		print_spec(args, spec, &buff);
	}
	if (buff.buff)
	{
		ft_putmem(buff.buff, buff.len);
		fn_free(buff.buff);
	}
	return (buff.total_put_in);
}

char	*ft_vasprintf(const char *str, va_list args)
{
	int				i;
	t_fmt_spec		spec;
	t_buffer		buff;

	i = 0;
	writer_init(&buff);
	buff.no_write = 1;
	while (str[i])
	{
		spec = parse(str, &i, args);
		print_spec(args, spec, &buff);
	}
	return (buff.buff);
}

int	ft_veprintf(const char *str, va_list args)
{
	int				i;
	t_fmt_spec		spec;
	t_buffer		buff;

	i = 0;
	writer_init(&buff);
	buff.out_fd = 2;
	while (str[i])
	{
		spec = parse(str, &i, args);
		print_spec(args, spec, &buff);
	}
	if (buff.buff)
	{
		ft_eputmem(buff.buff, buff.len);
		fn_free(buff.buff);
	}
	return (buff.total_put_in);
}

char	*ft_vaseprintf(const char *str, va_list args)
{
	int				i;
	t_fmt_spec		spec;
	t_buffer		buff;

	i = 0;
	writer_init(&buff);
	buff.no_write = 1;
	buff.out_fd = 2;
	while (str[i])
	{
		spec = parse(str, &i, args);
		print_spec(args, spec, &buff);
	}
	return (buff.buff);
}

int	ft_vfdprintf(int fd, const char *str, va_list args)
{
	int				i;
	t_fmt_spec		spec;
	t_buffer		buff;

	i = 0;
	writer_init(&buff);
	buff.out_fd = fd;
	while (str[i])
	{
		spec = parse(str, &i, args);
		print_spec(args, spec, &buff);
	}
	if (buff.buff)
	{
		ft_fdputmem(fd, buff.buff, buff.len);
		fn_free(buff.buff);
	}
	return (buff.total_put_in);
}
