/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timerisunset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:45:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/25 17:17:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

bool	timerisunset(const t_timeval *tvp)
{
	return (tvp->tv_sec == 0 && tvp->tv_usec == 0);
}
