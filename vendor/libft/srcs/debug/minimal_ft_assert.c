/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimal_ft_assert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:16:21 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:21:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * ft_assert - Minimal assertion function for 42 projects.
 * Triggers an intentional segmentation fault if the condition is false.
 * Uses 'volatile' to prevent compiler from optimizing away the fault.
 */
void	ft_assert(int cond)
{
	volatile char	*p;

	if (!cond)
	{
		p = (char *)0;
		*p = 42;
	}
}
