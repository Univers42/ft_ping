/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	loop_done(const t_ping *pg, long long last_send)
{
	if (ping_stopped())
		return (1);
	if (pg->deadline_us > 0 && now_us() - pg->start_us >= pg->deadline_us)
		return (1);
	if (pg->count >= 0 && pg->st.sent >= pg->count)
	{
		if (pg->st.recv + pg->st.errors >= pg->st.sent)
			return (1);
		if (now_us() - last_send >= pg->recv_wait_us)
			return (1);
	}
	return (0);
}

static long long	wait_deadline(const t_ping *pg, long long next,
		long long last)
{
	if (pg->count >= 0 && pg->st.sent >= pg->count)
		return (last + pg->recv_wait_us);
	return (next);
}

static int	maybe_send(t_ping *pg, long long *next, long long *last)
{
	if (pg->count >= 0 && pg->st.sent >= pg->count)
		return (0);
	if (now_us() < *next)
		return (0);
	if (send_echo(pg) < 0)
		return (-1);
	*last = now_us();
	*next = *last + pg->interval_us;
	return (0);
}

static int	send_preload(t_ping *pg)
{
	int	k;

	k = 0;
	while (k < pg->preload && (pg->count < 0 || pg->st.sent < pg->count))
	{
		if (send_echo(pg) < 0)
			return (-1);
		k++;
	}
	return (0);
}

int	ping_loop(t_ping *pg)
{
	long long	next;
	long long	last;

	if (pg->flood)
		return (flood_loop(pg));
	install_sigint();
	print_header(pg);
	pg->start_us = now_us();
	if (send_preload(pg) < 0)
		return (-1);
	next = now_us();
	last = next;
	while (!loop_done(pg, last))
	{
		if (maybe_send(pg, &next, &last) < 0)
			return (-1);
		if (wait_readable(pg->sock, wait_deadline(pg, next, last)))
			recv_one(pg);
	}
	print_stats(pg);
	return (0);
}
