/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:19:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

/* Singleton: one shared instance across all translation units */
t_tglob	*access_glob(void)
{
	static int		speeds_data[] = {
		0, 50, 75, 110, 135, 150, -2, -3, -6, -12,
		-18, -24, -48, -96, -192, -288, -384, -576, -1152};
	static char		esctab_data[] = " \007\010  \033\014 \012 \015 \011 \013 ";
	static t_tglob	g = {
		.pc = 0,
		.ospeed = 0,
		.speeds = speeds_data,
		.up = NULL,
		.bc = NULL,
		.tputs_baud_rate = 0,
		.esctab = esctab_data,
		.term_entry = NULL,
		.used_fallback = 0};

	return (&g);
}

int	get_baud_speed(void)
{
	t_tglob	*g;
	int		i;

	g = access_glob();
	i = g->ospeed;
	if (i == 0)
		return (g->tputs_baud_rate);
	if (i > 0 && i < 19)
		return (g->speeds[i]);
	return (0);
}

int	handle_octal(char **p, int c)
{
	int	size;
	int	c1;

	size = 0;
	while (size < 3)
	{
		size++;
		c1 = **p;
		if (c1 < '0' || c1 > '7')
			break ;
		c = c * 8 + (c1 - '0');
		(*p)++;
	}
	return (c);
}

int	handle_esctab(int c)
{
	t_tglob	*g;
	int		c1;

	g = access_glob();
	c1 = g->esctab[(c & ~040) - 0100];
	if (c1 != ' ')
		return (c1);
	return (c);
}
