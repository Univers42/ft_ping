/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_or_restore_signal_handlers.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:49:08 by alcacere          #+#    #+#             */
/*   Updated: 2025/11/26 19:50:54 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "trap.h"

void	reset_or_restore_signal_handlers(void (*func)(int))
{
	int	i;

	if (!func)
		return ;
	i = 1;
	while (i < NSIG)
	{
		func(i);
		i++;
	}
}
