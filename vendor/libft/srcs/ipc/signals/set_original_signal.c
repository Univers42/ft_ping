/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_original_signal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:53:26 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:53:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	set_original_signal(int sig, t_sig_handler handler)
{
	if (sig <= 0 || sig >= NSIG)
		return ;
	if (get_g_sig()->original_signals[sig]
		== (t_sig_handler)IMPOSSIBLE_TRAP_HANDLER)
		get_g_sig()->original_signals[sig] = handler;
	if (get_g_sig()->original_signals[sig] == SIG_IGN)
		get_g_sig()->sigmodes[sig] |= SIG_HARD_IGNORE;
}
