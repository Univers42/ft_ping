/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	init_ping(t_ping *pg)
{
	ft_memset(pg, 0, sizeof(*pg));
	pg->sock = -1;
	pg->ttl = PING_TTL;
	pg->payload_size = PING_PAYLOAD;
	pg->interval_us = PING_INTERVAL;
	pg->recv_wait_us = PING_RECV_WAIT;
	pg->count = -1;
	pg->id = (uint16_t)(getpid() & 0xffff);
	pg->st.min_us = -1;
}

static int	setup(t_ping *pg)
{
	pg->rbuf_sz = (size_t)pg->payload_size + 1024;
	pg->pkt = malloc((size_t)pg->payload_size + sizeof(struct icmphdr));
	pg->rbuf = malloc(pg->rbuf_sz);
	if (pg->pkt == NULL || pg->rbuf == NULL)
		return (error_msg("malloc", strerror(errno)));
	if (resolve_target(pg) != 0)
		return (-1);
	if (open_socket(pg) != 0)
		return (-1);
	return (0);
}

static void	cleanup(t_ping *pg)
{
	close_socket(pg);
	free(pg->pkt);
	free(pg->rbuf);
}

int	main(int ac, char **av)
{
	t_ping	pg;
	int		r;

	init_ping(&pg);
	r = parse_args(ac, av, &pg);
	if (r == ARGS_HELP)
	{
		print_usage(1);
		return (0);
	}
	if (r == ARGS_ERR)
		return (1);
	if (setup(&pg) != 0)
	{
		cleanup(&pg);
		return (1);
	}
	r = ping_loop(&pg);
	cleanup(&pg);
	if (r != 0 || pg.st.recv == 0)
		return (1);
	return (0);
}
