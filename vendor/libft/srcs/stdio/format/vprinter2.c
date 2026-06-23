/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprinter2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:18:53 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 13:31:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

/* Build the full formatted result into 'buff' (allocates buff->buff).
   Consumes va_list as usual. */
static void	build_formatted_buffer(t_buffer *buff,
						const char *str,
						va_list args)
{
	int			i;
	t_fmt_spec	spec;

	i = 0;
	writer_init(buff);
	buff->no_write = 1;
	buff->out_fd = -1;
	while (str[i])
	{
		spec = parse(str, &i, args);
		print_spec(args, spec, buff);
	}
}

/* finalize: copy into user buffer (size == (size_t)-1 => full copy),
   free internal buffer and return total_put_in */
static int	finalize_and_return(t_buffer *buff, char *buf, size_t size)
{
	size_t	copy;

	if (buf && buff->buff)
	{
		if (size == (size_t) - 1)
		{
			if (buff->len)
				ft_memcpy(buf, buff->buff, buff->len);
			buf[buff->len] = '\0';
		}
		else if (size > 0)
		{
			copy = (size_t)buff->len;
			if (copy > size - 1)
				copy = size - 1;
			if (copy)
				ft_memcpy(buf, buff->buff, copy);
			buf[copy] = '\0';
		}
	}
	if (buff->buff)
		fn_free(buff->buff);
	return (buff->total_put_in);
}

/* ft_vsnprintf: copy at most size-1 bytes and NUL-terminate if possible */
int	ft_vsnprintf(char *buf, size_t size, const char *str, va_list args)
{
	t_buffer	buff;

	build_formatted_buffer(&buff, str, args);
	return (finalize_and_return(&buff, buf, size));
}

/* ft_vsprintf: copy entire result and NUL-terminate */
int	ft_vsprintf(char *buf, const char *str, va_list args)
{
	t_buffer	buff;

	build_formatted_buffer(&buff, str, args);
	return (finalize_and_return(&buff, buf, (size_t)-1));
}
