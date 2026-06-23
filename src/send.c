/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	stamp_payload(t_ping *pg)
{
	struct timeval	tv;
	unsigned char	*data;

	data = pg->pkt + sizeof(struct icmphdr);
	gettimeofday(&tv, NULL);
	if ((size_t)pg->payload_size >= sizeof(tv))
		ft_memcpy(data, &tv, sizeof(tv));
	fill_pattern(pg, data);
}

int	send_echo(t_ping *pg)
{
	struct icmphdr	*icmp;
	size_t			len;
	ssize_t			n;

	icmp = (struct icmphdr *)pg->pkt;
	len = sizeof(*icmp) + (size_t)pg->payload_size;
	ft_memset(pg->pkt, 0, len);
	icmp->type = ICMP_ECHO;
	icmp->un.echo.id = htons(pg->id);
	icmp->un.echo.sequence = htons((uint16_t)pg->seq);
	stamp_payload(pg);
	icmp->checksum = icmp_checksum(pg->pkt, len);
	n = sendto(pg->sock, pg->pkt, len, 0, (struct sockaddr *)&pg->dst,
			sizeof(pg->dst));
	if (n < 0)
		return (error_msg("sendto", strerror(errno)));
	if (pg->flood)
		ft_putchar_fd('.', 1);
	pg->st.sent++;
	pg->seq++;
	return (0);
}
