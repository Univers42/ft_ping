/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:44:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/25 17:17:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

void	timerset(t_timeval *tvp, time_t s, suseconds_t u)
{
	tvp->tv_sec = s;
	tvp->tv_usec = u;
}
