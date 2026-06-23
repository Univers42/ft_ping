/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:45:11 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:47:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"
#include "ft_memory.h"

void	mask_dfl_sigact(void (*handler)(int), int sa_flags, int ig_quits)
{
	t_sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = sa_flags;
	sigaction(SIGINT, &act, NULL);
	if (ig_quits)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, SIG_DFL);
}

void	set_unwind_sig(void)
{
	mask_dfl_sigact(set_wind, SA_RESTART, 1);
}

void	set_unwind_sig_norestart(void)
{
	mask_dfl_sigact(set_wind, 0, 1);
}

void	bg_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
