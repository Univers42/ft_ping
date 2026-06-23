/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	parse_seconds(const char *s, long long *us)
{
	long long	whole;
	long long	frac;
	long long	scale;

	whole = 0;
	while (*s >= '0' && *s <= '9')
		whole = whole * 10 + (*s++ - '0');
	frac = 0;
	scale = 1000000;
	if (*s == '.' && *(s + 1))
	{
		s++;
		while (*s >= '0' && *s <= '9' && scale > 1)
		{
			scale /= 10;
			frac += (*s++ - '0') * scale;
		}
	}
	if (*s != '\0')
		return (error_msg("invalid time value", NULL), -1);
	*us = whole * 1000000LL + frac;
	return (0);
}

static int	parse_int(const char *s, int *out, int lo, int hi)
{
	long long	v;

	if (*s == '\0')
		return (-1);
	v = 0;
	while (*s >= '0' && *s <= '9')
	{
		v = v * 10 + (*s++ - '0');
		if (v > 2147483647LL)
			return (-1);
	}
	if (*s != '\0' || v < lo || v > hi)
		return (-1);
	*out = (int)v;
	return (0);
}

static int	set_int(t_ping *pg, int c, char *arg)
{
	int	v;

	if (c == 'c' && parse_int(arg, &v, 1, INT_MAX) == 0)
	{
		pg->count = v;
		return (0);
	}
	if (c == 's' && parse_int(arg, &pg->payload_size, 0, PING_SIZEMAX) == 0)
		return (0);
	if (c == 'l' && parse_int(arg, &pg->preload, 1, 65536) == 0)
		return (0);
	if (c == 'T' && parse_int(arg, &pg->tos, 0, 255) == 0)
		return (0);
	if (c == OPT_TTL && parse_int(arg, &pg->ttl, 1, 255) == 0)
		return (0);
	return (error_msg("invalid option value", arg), -1);
}

int	dispatch_opt(t_ping *pg, int c, char *arg)
{
	if (c == 'v')
		pg->verbose = 1;
	else if (c == 'n')
		pg->numeric = 1;
	else if (c == 'r')
		pg->dontroute = 1;
	else if (c == 'f')
		pg->flood = 1;
	else if (c == OPT_IPTS)
		pg->ip_ts = 1;
	else if (c == 'i')
		return (parse_seconds(arg, &pg->interval_us));
	else if (c == 'w')
		return (parse_seconds(arg, &pg->deadline_us));
	else if (c == 'W')
		return (parse_seconds(arg, &pg->recv_wait_us));
	else if (c == 'p')
		return (parse_pattern(pg, arg));
	else
		return (set_int(pg, c, arg));
	return (0);
}
