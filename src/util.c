/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

long long	now_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv_to_us(&tv));
}

long long	tv_to_us(const struct timeval *tv)
{
	return ((long long)tv->tv_sec * 1000000LL + (long long)tv->tv_usec);
}

int	error_msg(const char *what, const char *why)
{
	ft_eprintf("ft_ping: %s", what);
	if (why != NULL)
		ft_eprintf(": %s", why);
	ft_eprintf("\n");
	return (-1);
}
