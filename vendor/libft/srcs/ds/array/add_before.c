/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_before.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:52:57 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:36:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// Insert new before ae in the circular list (ae must not be NULL)
void	add_before(t_arr_elem *ae, t_arr_elem *elem)
{
	ae->prev->next = elem;
	elem->prev = ae->prev;
	ae->prev = elem;
	elem->next = ae;
}
