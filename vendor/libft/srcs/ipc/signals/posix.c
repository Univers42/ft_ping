/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 05:48:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 20:06:37 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"
#include "quit.h"

/* Singleton accessor for global termination state */

void	ft_sigfillset(t_sigset *set)
{
	unsigned int	n;

	if (!set)
		return ;
	if (NSIG >= 32)
		n = 32U;
	else
		n = (unsigned int)NSIG;
	if (n == 0)
		*set = 0U;
	else if (n == 32)
		*set = ~0U;
	else
		*set = (1U << n) - 1U;
}

void	ft_sigaddset(t_sigset *set, int sig)
{
	*set |= ft_sigmask(sig);
}

void	ft_sigdelset(t_sigset *set, int sig)
{
	*set &= ~ft_sigmask(sig);
}

void	check_sigterm(void)
{
	if (get_g_term()->sigterm_received)
		termsig_handler(SIGTERM);
}

void	zreset_if_needed(void)
{
	if (get_g_term()->interrupt_state)
		zreset();
}
