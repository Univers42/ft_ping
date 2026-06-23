/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_signames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:48:40 by alcacere          #+#    #+#             */
/*   Updated: 2025/11/26 20:49:57 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	initialize_signames(void)
{
	int	i;

	i = 0;
	while (i < NSIG)
	{
		get_g_sig()->signal_name[i] = (char *)strsignal(i);
		i++;
	}
}
