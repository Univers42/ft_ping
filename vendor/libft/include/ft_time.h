/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:11:44 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:12:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H
/* Feature test macros - define before any system includes */
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef _BSD_SOURCE
#  define _BSD_SOURCE
# endif

# include "ft_stddef.h"
# include <stdio.h>
# include <sys/types.h>
# include <time.h>
# include <stdbool.h>
/* ensure timeval/timespec definitions */
# include <sys/time.h>

/* portable typedefs used across the time module */
/* t_time is provided by ft_stddef.h (uint64_t). Do not redefine it here. */
typedef struct timespec	t_timespec;

# define CLOCK_TICK 60
// Fix: Use struct timeval, not just timeval
typedef struct timeval	t_timeval;

typedef struct s_chrono
{
	struct timeval	start;
	long			last_ms;
}	t_chrono;

t_time	ft_time(void);
t_time	ft_usleep(t_time duration);
t_time	ft_delta_time(t_time first, t_time second);
t_time	cur_time(void);
t_time	elapsed_time(t_time start);
bool	ft_timerisset(const t_timeval *tvp);

#endif
