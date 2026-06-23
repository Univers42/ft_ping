/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uw_maaybe_set_return_trap.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:48:01 by alcacere          #+#    #+#             */
/*   Updated: 2025/11/26 20:48:13 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	uw_maybe_set_return_trap(void *command)
{
	trap_if_untrapped(RETURN_TRAP, command);
}
