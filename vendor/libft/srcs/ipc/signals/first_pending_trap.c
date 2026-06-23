/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pending_trap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcacere <alcacere@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:18:07 by alcacere          #+#    #+#             */
/*   Updated: 2025/11/26 19:18:43 by alcacere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

int	first_pending_trap(void)
{
	return (next_pending_trap(1));
}
