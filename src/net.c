/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	set_ttl(int fd, int ttl)
{
	if (setsockopt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		return (error_msg("setsockopt IP_TTL", strerror(errno)));
	return (0);
}

int	open_socket(t_ping *pg)
{
	pg->sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (pg->sock < 0)
	{
		if (errno == EPERM || errno == EACCES)
			return (error_msg("socket",
					"raw socket requires root or CAP_NET_RAW"));
		return (error_msg("socket", strerror(errno)));
	}
	if (apply_sockopts(pg) < 0)
	{
		close(pg->sock);
		pg->sock = -1;
		return (-1);
	}
	return (0);
}

void	close_socket(t_ping *pg)
{
	if (pg->sock >= 0)
		close(pg->sock);
	pg->sock = -1;
}
