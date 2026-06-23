/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 21:16:02 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:37:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

t_glob_sig	*get_g_sig(void)
{
	static t_glob_sig	g_sig = {0};

	return (&g_sig);
}

/* return the appropriate signal handler (typed) */
t_sig_handler	trap_to_sighandler(int sig)
{
	if (get_g_sig()->sigmodes[sig] & SIG_HARD_IGNORE)
		return (SIG_IGN);
	else if (get_g_sig()->sigmodes[sig] & SIG_TRAPPED)
		return (trap_handler);
	else
		return (SIG_DFL);
}

void	trap_if_untrapped(int sig, const char *command)
{
	if ((get_g_sig()->sigmodes[sig] & SIG_TRAPPED) == 0)
		set_signal(sig, command);
}

int	signal_is_trapped(int sig)
{
	return (get_g_sig()->sigmodes[sig] & SIG_TRAPPED);
}

void	set_wind(int sig)
{
	(void)sig;
	get_g_sig()->should_unwind = SIGINT;
}
