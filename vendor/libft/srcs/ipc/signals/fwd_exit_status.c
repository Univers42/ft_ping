/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fwd_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:53:33 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:33:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include "trap.h"
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

void	fwd_exstatus(int st, bool c)
{
	ft_assert(st != -1);
	if (c)
	{
		set_signal_handler(SIGINT, SIG_DFL);
		set_signal_handler(SIGQUIT, SIG_DFL);
		kill(0, SIGINT);
		while (true)
			;
	}
	exit(st);
}
