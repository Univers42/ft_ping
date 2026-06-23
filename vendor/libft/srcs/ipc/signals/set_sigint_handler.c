/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sigint_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:53:31 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:30:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	trap_handler(int sig)
{
	set_trap_state(sig);
}

void	sigint_sighandler(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	termsig_sighandler(int sig)
{
	(void)sig;
}

/* Return type is a signal handler function pointer */
t_sig_handler	set_sigint_handler(void)
{
	if (get_g_sig()->sigmodes[SIGINT] & SIG_HARD_IGNORE)
		return (SIG_IGN);
	else if (get_g_sig()->sigmodes[SIGINT] & SIG_IGNORED)
		return (set_signal_handler(SIGINT, SIG_IGN));
	else if (get_g_sig()->sigmodes[SIGINT] & SIG_TRAPPED)
		return (set_signal_handler(SIGINT, trap_handler));
	else if (get_g_sig()->interactive)
		return (set_signal_handler(SIGINT, sigint_sighandler));
	else
		return (set_signal_handler(SIGINT, termsig_sighandler));
}
