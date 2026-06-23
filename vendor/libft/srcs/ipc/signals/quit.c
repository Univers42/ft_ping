/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 02:01:20 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 02:02:01 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quit.h"

/* Provide the singleton accessor for the termination state used across the
   signal library. */
struct s_termg	*get_g_term(void)
{
	static struct s_termg	g_term = {0};

	return (&g_term);
}
