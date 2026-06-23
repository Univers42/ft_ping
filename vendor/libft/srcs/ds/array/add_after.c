/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_after.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:52:36 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:34:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// Insert new after ae in the circular list (ae must not be NULL)
void	add_after(t_arr_elem *ae, t_arr_elem *elem)
{
	ae->next->prev = elem;
	elem->next = ae->next;
	elem->prev = ae;
	ae->next = elem;
}
