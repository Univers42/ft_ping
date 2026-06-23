/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int	flood_done(const t_ping *pg)
{
	if (ping_stopped())
		return (1);
	if (pg->deadline_us > 0 && now_us() - pg->start_us >= pg->deadline_us)
		return (1);
	if (pg->count >= 0 && pg->st.sent >= pg->count
		&& pg->st.recv + pg->st.errors >= pg->st.sent)
		return (1);
	return (0);
}

int	flood_loop(t_ping *pg)
{
	install_sigint();
	print_header(pg);
	pg->start_us = now_us();
	while (!flood_done(pg))
	{
		if (pg->count < 0 || pg->st.sent < pg->count)
		{
			if (send_echo(pg) < 0)
				return (-1);
		}
		while (wait_readable(pg->sock, now_us()))
			recv_one(pg);
	}
	ft_putchar_fd('\n', 1);
	print_stats(pg);
	return (0);
}
