/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:29 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:54:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	get_all_original_signals(void)
{
	register int	i;

	i = 0;
	while (++i < NSIG)
		get_original_signal(i);
}

void	get_orig_sig(int sig)
{
	t_sig_handler	handler;

	if (sig <= 0 || sig >= NSIG)
		return ;
	handler = set_signal_handler(sig, SIG_DFL);
	get_g_sig()->original_signals[sig] = handler;
	if (get_g_sig()->original_signals[sig] == SIG_IGN)
		get_g_sig()->sigmodes[sig] |= SIG_HARD_IGNORE;
}

void	get_original_signal(int sig)
{
	if (sig > 0 && sig < NSIG && get_g_sig()->original_signals[sig]
		== (t_sig_handler)IMPOSSIBLE_TRAP_HANDLER)
		get_orig_sig(sig);
}
