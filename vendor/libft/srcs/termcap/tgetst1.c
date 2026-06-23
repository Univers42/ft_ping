/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetst1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 00:50:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 22:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

int	handle_octal(char **p, int c);
int	handle_esctab(int c);

static int	handle_backslash_escape(char **p)
{
	int	c;

	c = **p;
	(*p)++;
	if (c >= '0' && c <= '7')
	{
		c -= '0';
		c = handle_octal(p, c);
		return (c);
	}
	if (c >= 0100 && c < 0200)
		return (handle_esctab(c));
	return (c);
}

static int	process_escape_char(char **p)
{
	int	c;

	c = **p;
	(*p)++;
	if (c == '^')
	{
		c = **p;
		(*p)++;
		if (c == '?')
			return (0177);
		return (c & 037);
	}
	if (c == '\\')
		return (handle_backslash_escape(p));
	return (c);
}

static int	compute_size(char *ptr)
{
	char	*p;
	int		c;

	p = ptr;
	while (1)
	{
		c = *p++;
		if (c == '\0' || c == ':' || c == '\n')
			break ;
	}
	return (p - ptr + 1);
}

static char	*copy_value(char *ptr, char *ret, char **area)
{
	char	*p;
	char	*r;
	int		c;

	p = ptr;
	r = ret;
	while (1)
	{
		c = *p;
		if (c == '\0' || c == ':' || c == '\n')
			break ;
		*r++ = process_escape_char(&p);
	}
	*r = '\0';
	if (area)
		*area = r + 1;
	return (ret);
}

char	*tgetst1(char *ptr, char **area)
{
	char	*ret;
	int		size;

	if (!ptr)
		return (NULL);
	if (!area)
	{
		size = compute_size(ptr);
		ret = (char *)fn_malloc(size);
	}
	else
		ret = *area;
	return (copy_value(ptr, ret, area));
}
