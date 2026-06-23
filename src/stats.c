/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

long long	isqrt_ll(long long n)
{
	long long	x;
	long long	y;

	if (n <= 0)
		return (0);
	x = n;
	y = (x + 1) / 2;
	while (y < x)
	{
		x = y;
		y = (x + n / x) / 2;
	}
	return (x);
}

void	stats_add(t_stats *st, long long us)
{
	if (st->min_us < 0 || us < st->min_us)
		st->min_us = us;
	if (us > st->max_us)
		st->max_us = us;
	st->sum_us += us;
	st->sum_sq += us * us;
}

static void	print_counts(const t_ping *pg)
{
	int	loss;

	loss = 0;
	if (pg->st.sent > 0)
		loss = (int)((pg->st.sent - pg->st.recv) * 100 / pg->st.sent);
	ft_printf("--- %s ping statistics ---\n", pg->host);
	ft_printf("%d packets transmitted, %d packets received, %d%% packet loss\n",
		(int)pg->st.sent, (int)pg->st.recv, loss);
}

void	print_stats(const t_ping *pg)
{
	long long	avg;
	long long	sd;

	print_counts(pg);
	if (pg->st.recv <= 0 || pg->st.min_us < 0)
		return ;
	avg = pg->st.sum_us / pg->st.recv;
	sd = isqrt_ll(pg->st.sum_sq / pg->st.recv - avg * avg);
	ft_printf("round-trip min/avg/max/stddev = "
		"%d.%03d/%d.%03d/%d.%03d/%d.%03d ms\n",
		(int)(pg->st.min_us / 1000), (int)(pg->st.min_us % 1000),
		(int)(avg / 1000), (int)(avg % 1000),
		(int)(pg->st.max_us / 1000), (int)(pg->st.max_us % 1000),
		(int)(sd / 1000), (int)(sd % 1000));
}
