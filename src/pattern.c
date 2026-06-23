/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	hexval(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

static int	add_byte(t_ping *pg, const char **s)
{
	int	hi;
	int	lo;

	hi = hexval(**s);
	if (hi < 0)
		return (-1);
	(*s)++;
	lo = 0;
	if (**s != '\0' && hexval(**s) >= 0)
	{
		lo = hexval(**s);
		(*s)++;
	}
	pg->pattern[pg->pattern_len++] = (unsigned char)((hi << 4) | lo);
	return (0);
}

int	parse_pattern(t_ping *pg, const char *s)
{
	pg->pattern_len = 0;
	while (*s != '\0' && pg->pattern_len < PING_PATMAX)
	{
		if (add_byte(pg, &s) != 0)
			return (error_msg("invalid pattern value", NULL), -1);
	}
	if (*s != '\0' || pg->pattern_len == 0)
		return (error_msg("invalid pattern value", NULL), -1);
	return (0);
}

void	fill_pattern(const t_ping *pg, unsigned char *data)
{
	size_t	start;
	size_t	i;

	start = sizeof(struct timeval);
	i = start;
	while (i < (size_t)pg->payload_size)
	{
		if (pg->pattern_len > 0)
			data[i] = pg->pattern[(i - start) % (size_t)pg->pattern_len];
		else
			data[i] = (unsigned char)i;
		i++;
	}
}
