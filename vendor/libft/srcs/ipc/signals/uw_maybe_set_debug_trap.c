/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uw_maybe_set_debug_trap.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:57:02 by alcacere          #+#    #+#             */
/*   Updated: 2025/11/26 19:57:16 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "trap.h"

/* Separate function to call when functions and sourced files want to restore
	 the original version of the DEBUG trap before returning.  Unless the -T
	 option is set, source and shell function execution save the old debug trap
	 and unset the trap.  If the function or sourced file changes the DEBUG trap,
	 SIG_TRAPPED will be set and we don't bother restoring the original
	 trap string.
	 This is used by both functions and the source builtin. */
void	uw_maybe_set_debug_trap(void *command)
{
	trap_if_untrapped(DEBUG_TRAP, command);
}
