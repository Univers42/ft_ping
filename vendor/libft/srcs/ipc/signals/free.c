/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:42 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:37:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"
#include "ft_string.h"

void	free_trap_command(int sig)
{
	if ((get_g_sig()->sigmodes[sig] & SIG_TRAPPED)
		&& get_g_sig()->trap_list[sig]
		&& (ft_strcmp(get_g_sig()->trap_list[sig], (char *)IGNORE_SIG) != 0)
		&& (ft_strcmp(get_g_sig()->trap_list[sig], (char *)DEFAULT_SIG) != 0)
		&& (ft_strcmp(get_g_sig()->trap_list[sig],
				(char *)TRAP_IMPOSSIBLE) != 0))
		fn_free(get_g_sig()->trap_list[sig]);
}

void	free_trap_string(int sig)
{
	change_signal(sig, (char *)DEFAULT_SIG);
	get_g_sig()->sigmodes[sig] &= ~SIG_TRAPPED;
}

void	free_trap_strings(void)
{
	register int	i;

	i = -1;
	while (++i < NSIG)
		if (ft_strcmp(get_g_sig()->trap_list[i], (char *)IGNORE_SIG) != 0)
			free_trap_string(i);
	i = NSIG - 1;
	while (++i < BASH_NSIG_TOTAL)
	{
		if ((get_g_sig()->sigmodes[i] & SIG_TRAPPED) == 0)
		{
			free_trap_string(i);
			get_g_sig()->trap_list[i] = (char *) NULL;
		}
	}
}
