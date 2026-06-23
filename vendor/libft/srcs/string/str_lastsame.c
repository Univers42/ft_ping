/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lastsame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:40 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/27 20:44:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	str_lastsame(const char *old, const char *new)
{
	const char	*o;
	const char	*n;

	if (old == 0 || *old == '\0' || new == 0 || *new == '\0')
		return (0);
	o = old + ft_strlen(old) - 1;
	n = new + ft_strlen(new) - 1;
	while (o > old && n > new && (*o == *n))
	{
		o--;
		n--;
	}
	return (o - old);
}
