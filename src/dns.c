/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	resolve_target(t_ping *pg)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				gai;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	gai = getaddrinfo(pg->host, NULL, &hints, &res);
	if (gai != 0)
		return (error_msg(pg->host, gai_strerror(gai)));
	pg->dst = *(struct sockaddr_in *)res->ai_addr;
	freeaddrinfo(res);
	if (inet_ntop(AF_INET, &pg->dst.sin_addr, pg->dst_str,
			sizeof(pg->dst_str)) == NULL)
		return (error_msg("inet_ntop", strerror(errno)));
	return (0);
}
