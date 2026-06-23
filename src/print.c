/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_header(const t_ping *pg)
{
	ft_printf("PING %s (%s): %d data bytes", pg->host, pg->dst_str,
		pg->payload_size);
	if (pg->verbose)
		ft_printf(", id 0x%x = %d", pg->id, pg->id);
	ft_printf("\n");
}

void	print_reply(const t_ping *pg, int seq, int ttl, long long us)
{
	ft_printf("%d bytes from %s: icmp_seq=%d ttl=%d",
		pg->payload_size + 8, pg->dst_str, seq, ttl);
	if (us >= 0)
		ft_printf(" time=%d.%03d ms", (int)(us / 1000), (int)(us % 1000));
	ft_printf("\n");
}

void	print_error(const char *from_ip, int bytes, const char *reason)
{
	ft_printf("%d bytes from %s: %s\n", bytes, from_ip, reason);
}
