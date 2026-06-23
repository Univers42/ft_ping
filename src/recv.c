/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	wait_readable(int fd, long long deadline_us)
{
	fd_set			rfds;
	struct timeval	tv;
	long long		left;

	left = deadline_us - now_us();
	if (left < 0)
		left = 0;
	tv.tv_sec = (time_t)(left / 1000000LL);
	tv.tv_usec = (suseconds_t)(left % 1000000LL);
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	if (select(fd + 1, &rfds, NULL, NULL, &tv) <= 0)
		return (0);
	return (1);
}

static int	on_echo(t_ping *pg, struct icmphdr *icmp, int rttl, ssize_t n)
{
	struct timeval	tv;
	unsigned char	*data;
	long long		us;

	if (ntohs(icmp->un.echo.id) != pg->id)
		return (0);
	pg->st.recv++;
	data = (unsigned char *)icmp + sizeof(*icmp);
	us = -1;
	if ((size_t)(data - pg->rbuf) + sizeof(tv) <= (size_t)n)
	{
		ft_memcpy(&tv, data, sizeof(tv));
		us = now_us() - tv_to_us(&tv);
		stats_add(&pg->st, us);
	}
	if (pg->flood)
		ft_putchar_fd('\b', 1);
	else
		print_reply(pg, ntohs(icmp->un.echo.sequence), rttl, us);
	return (1);
}

static struct icmphdr	*embedded_icmp(const t_ping *pg, struct icmphdr *icmp,
		ssize_t n)
{
	struct iphdr		*oip;
	const unsigned char	*end;
	size_t				ihl;

	end = pg->rbuf + n;
	oip = (struct iphdr *)((unsigned char *)icmp + sizeof(*icmp));
	if ((unsigned char *)oip + sizeof(*oip) > end)
		return (NULL);
	ihl = (size_t)oip->ihl * 4;
	if ((unsigned char *)oip + ihl + sizeof(struct icmphdr) > end)
		return (NULL);
	return ((struct icmphdr *)((unsigned char *)oip + ihl));
}

static int	on_err(t_ping *pg, struct icmphdr *icmp, const char *from,
		ssize_t n)
{
	struct icmphdr	*oicmp;
	const char		*reason;

	if (icmp->type != ICMP_TIME_EXCEEDED && icmp->type != ICMP_DEST_UNREACH)
		return (0);
	oicmp = embedded_icmp(pg, icmp, n);
	if (oicmp == NULL || ntohs(oicmp->un.echo.id) != pg->id)
		return (0);
	pg->st.errors++;
	reason = "Destination unreachable";
	if (icmp->type == ICMP_TIME_EXCEEDED)
		reason = "Time to live exceeded";
	print_error(from, (int)n, reason);
	return (1);
}

int	recv_one(t_ping *pg)
{
	struct iphdr	*ip;
	struct icmphdr	*icmp;
	char			from[INET_ADDRSTRLEN];
	ssize_t			n;
	int				r;

	n = recvfrom(pg->sock, pg->rbuf, pg->rbuf_sz, 0, NULL, NULL);
	if (n < 0 || (size_t)n < sizeof(struct iphdr))
		return (0);
	ip = (struct iphdr *)pg->rbuf;
	if ((size_t)n < (size_t)ip->ihl * 4 + sizeof(struct icmphdr))
		return (0);
	icmp = (struct icmphdr *)(pg->rbuf + (size_t)ip->ihl * 4);
	inet_ntop(AF_INET, &ip->saddr, from, sizeof(from));
	if (icmp->type != ICMP_ECHOREPLY)
		return (on_err(pg, icmp, from, n));
	r = on_echo(pg, icmp, (int)ip->ttl, n);
	if (r == 1 && pg->ip_ts && !pg->flood)
		print_ip_ts(ip);
	return (r);
}
