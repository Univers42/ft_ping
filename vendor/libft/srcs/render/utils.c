/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:05:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/21 20:01:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "ft_stdio.h"
#include <unistd.h>
#include <sys/time.h>

void	ft_typewriter_effect(const char *text, int delay_ms)
{
	int	i;

	if (!text)
		return ;
	i = 0;
	while (text[i])
	{
		ft_printf("%c", text[i]);
		fflush(stdout);
		sleep(delay_ms * 1);
		i++;
	}
}

void	ft_print_loading_spinner(int duration_ms)
{
	const char	*spinner;
	int			elapsed;
	int			frame;

	spinner = "|/-\\";
	elapsed = 0;
	frame = 0;
	while (elapsed < duration_ms)
	{
		ft_printf("\r%c", spinner[frame % 4]);
		fflush(stdout);
		sleep(1);
		elapsed += 100;
		frame++;
	}
	ft_printf("\r \r");
	fflush(stdout);
}
