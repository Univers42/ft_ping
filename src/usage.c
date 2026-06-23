/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static const char	*g_usage[] = {
	"Usage: ft_ping [OPTION...] HOST",
	"Send ICMP ECHO_REQUEST packets to network hosts.",
	"",
	"  -c NUMBER      stop after sending NUMBER packets",
	"  -i NUMBER      seconds between sending each packet",
	"  -v             verbose output",
	"  -?             give this help list",
	"",
	"Run as root (raw sockets require CAP_NET_RAW).",
	NULL
};

void	print_usage(int fd)
{
	int	i;

	i = 0;
	while (g_usage[i] != NULL)
	{
		ft_putstr_fd((char *)g_usage[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}
