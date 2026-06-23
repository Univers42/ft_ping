/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:25:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/26 19:24:15 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"
#include <signal.h>

char	*signal_name(int sig)
{
	if (sig >= 0 && sig < NSIG && get_g_sig()->signal_name[sig])
		return (get_g_sig()->signal_name[sig]);
	if (sig > 0 && sig < NSIG)
		return ((char *)strsignal(sig));
	if (sig == EXIT_TRAP)
		return ("EXIT");
	if (sig == DEBUG_TRAP)
		return ("DEBUG");
	if (sig == ERROR_TRAP)
		return ("ERROR");
	if (sig == RETURN_TRAP)
		return ("RETURN");
	return ((char *)"invalid signal number");
}
