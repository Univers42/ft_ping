/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:39:50 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/25 20:47:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include <stdlib.h>
#include <unistd.h>

t_time	cur_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((t_time)tv.tv_sec * 1000 + (t_time)(tv.tv_usec / 1000));
}

t_time	elapsed_time(t_time start)
{
	return (cur_time() - start);
}

t_time	ft_delta_time(t_time first, t_time second)
{
	return (second - first);
}

t_time	ft_usleep(t_time duration)
{
	t_time	start;
	t_time	limit;

	start = cur_time();
	limit = start + duration;
	while (cur_time() < limit)
		usleep(1000);
	return (elapsed_time(start));
}
