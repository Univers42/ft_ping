/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static void	dump_ts(const unsigned char *opt)
{
	uint32_t	ts;
	int			off;
	int			fill;

	ft_printf("TS:");
	fill = opt[2] - 1;
	if (fill > opt[1])
		fill = opt[1];
	off = 4;
	while (off + 4 <= fill)
	{
		ft_memcpy(&ts, opt + off, sizeof(ts));
		ft_printf(" %u", ntohl(ts));
		off += 4;
	}
	ft_printf("\n");
}

void	print_ip_ts(const struct iphdr *ip)
{
	const unsigned char	*opt;
	const unsigned char	*end;

	opt = (const unsigned char *)ip + sizeof(*ip);
	end = (const unsigned char *)ip + (size_t)ip->ihl * 4;
	while (opt < end && *opt != IPOPT_END)
	{
		if (*opt == IPOPT_TIMESTAMP)
		{
			dump_ts(opt);
			return ;
		}
		if (*opt == IPOPT_NOOP)
			opt++;
		else if (opt[1] >= 2)
			opt = opt + opt[1];
		else
			return ;
	}
}
