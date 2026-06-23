/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/23 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static const struct option	g_long[] = {
{"verbose", 0, NULL, 'v'},
{"count", 1, NULL, 'c'},
{"interval", 1, NULL, 'i'},
{"numeric", 0, NULL, 'n'},
{"ignore-routing", 0, NULL, 'r'},
{"tos", 1, NULL, 'T'},
{"flood", 0, NULL, 'f'},
{"preload", 1, NULL, 'l'},
{"pattern", 1, NULL, 'p'},
{"size", 1, NULL, 's'},
{"timeout", 1, NULL, 'w'},
{"linger", 1, NULL, 'W'},
{"ttl", 1, NULL, OPT_TTL},
{"ip-timestamp", 0, NULL, OPT_IPTS},
{NULL, 0, NULL, 0}
};

static int	scan_help(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-?") == 0 || ft_strcmp(av[i], "--help") == 0
			|| ft_strcmp(av[i], "--usage") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	parse_args(int ac, char **av, t_ping *pg)
{
	int	c;

	if (scan_help(ac, av))
		return (ARGS_HELP);
	opterr = 0;
	c = getopt_long(ac, av, ":vc:i:nrT:fl:p:s:w:W:", g_long, NULL);
	while (c != -1)
	{
		if (c == ':' || c == '?')
			return (error_msg("invalid option or missing argument",
					av[optind - 1]), ARGS_ERR);
		if (dispatch_opt(pg, c, optarg) != 0)
			return (ARGS_ERR);
		c = getopt_long(ac, av, ":vc:i:nrT:fl:p:s:w:W:", g_long, NULL);
	}
	if (optind >= ac)
		return (error_msg("missing host operand", NULL), ARGS_ERR);
	pg->host = av[optind];
	return (ARGS_OK);
}
