/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/19 15:31:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "ft_stdio.h"
#include "ft_colors.h"

void	ft_print_menu(char **options, int count, int selected)
{
	int	i;

	i = 0;
	ft_printf("\n%s┌─ SELECT OPTION ─┐%s\n", ASCII_CYAN, RESET_TERM);
	while (i < count)
	{
		if (i == selected)
			ft_printf("%s│ ► %-12s │%s\n", ASCII_GREEN, options[i], RESET_TERM);
		else
			ft_printf("%s│   %-12s │%s\n", ASCII_WHITE, options[i], RESET_TERM);
		i++;
	}
	ft_printf("%s└─────────────────┘%s\n", ASCII_CYAN, RESET_TERM);
}

static void	print_timeline_item(char *time, char *event, int is_last)
{
	if (is_last)
		ft_printf("%s└─ %s%s %s%s\n", ASCII_CYAN, time, RESET_TERM, event,
			RESET_TERM);
	else
	{
		ft_printf("%s├─ %s%s %s%s\n", ASCII_CYAN, time, RESET_TERM, event,
			RESET_TERM);
		ft_printf("%s│%s\n", ASCII_CYAN, RESET_TERM);
	}
}

void	ft_print_timeline(char **events, char **times, int count)
{
	int	i;

	i = 0;
	ft_printf("\n%s── TIMELINE ──%s\n", ASCII_CYAN, RESET_TERM);
	while (i < count)
	{
		print_timeline_item(times[i], events[i], (i == count - 1));
		i++;
	}
}

void	print_graph_row(int *values, int count, t_graph_params params)
{
	int	i;
	int	bar_height;

	i = 0;
	while (i < count)
	{
		bar_height = (values[i] * params.max_height) / params.max_val;
		if (bar_height >= params.row)
			ft_printf("%s█%s", ASCII_GREEN, RESET_TERM);
		else
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
}
