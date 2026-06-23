/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockopt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	set_tos(int fd, int tos)
{
	if (setsockopt(fd, IPPROTO_IP, IP_TOS, &tos, sizeof(tos)) < 0)
		return (error_msg("setsockopt IP_TOS", strerror(errno)));
	return (0);
}

static int	set_dontroute(int fd)
{
	int	on;

	on = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_DONTROUTE, &on, sizeof(on)) < 0)
		return (error_msg("setsockopt SO_DONTROUTE", strerror(errno)));
	return (0);
}

static int	set_ipts(int fd)
{
	unsigned char	opt[8];

	ft_memset(opt, 0, sizeof(opt));
	opt[0] = IPOPT_TIMESTAMP;
	opt[1] = 8;
	opt[2] = 5;
	opt[3] = IPOPT_TS_TSONLY;
	if (setsockopt(fd, IPPROTO_IP, IP_OPTIONS, opt, sizeof(opt)) < 0)
		return (error_msg("setsockopt IP_OPTIONS", strerror(errno)));
	return (0);
}

int	apply_sockopts(t_ping *pg)
{
	if (set_ttl(pg->sock, pg->ttl) < 0)
		return (-1);
	if (pg->tos != 0 && set_tos(pg->sock, pg->tos) < 0)
		return (-1);
	if (pg->dontroute && set_dontroute(pg->sock) < 0)
		return (-1);
	if (pg->ip_ts && set_ipts(pg->sock) < 0)
		return (-1);
	return (0);
}
