/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timespec_to_timeval.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:42:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/01 00:34:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include <signal.h>

void	timespec_to_timeval(t_timeval *tv, const t_timespec *ts)
{
	tv->tv_sec = ts->tv_sec;
	tv->tv_usec = ts->tv_nsec / 1000;
}
