/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timercmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:45:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/01 00:34:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "ft_string.h"

/**
 * two timeva struct with an operator &a, &b, <
 */
bool	ft_timercmp(const t_timeval *a, const t_timeval *b, const char *cmp)
{
	if (a->tv_sec == b->tv_sec)
	{
		if (ft_strcmp(cmp, "<") == 0)
			return (a->tv_usec < b->tv_usec);
		if (ft_strcmp(cmp, ">") == 0)
			return (a->tv_usec > b->tv_usec);
		if (ft_strcmp(cmp, "==") == 0)
			return (a->tv_usec == b->tv_usec);
	}
	else
	{
		if (ft_strcmp(cmp, "<") == 0)
			return (a->tv_sec < b->tv_sec);
		if (ft_strcmp(cmp, ">") == 0)
			return (a->tv_sec > b->tv_sec);
		if (ft_strcmp(cmp, "==") == 0)
			return (a->tv_sec == b->tv_sec);
	}
	return (false);
}
