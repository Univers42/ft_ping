/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_custom_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 23:32:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/26 23:36:49 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

bool	is_custom_set(int c, const char *set)
{
	while (*set)
	{
		if ((unsigned char)c == *set)
			return (true);
		set++;
	}
	return (false);
}
