/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:38:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/21 20:33:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stddef.h"
#include <stdlib.h>
#include "ft_string.h"

char	*ft_strndup(const char *s1, t_size n)
{
	char	*dup;
	t_size	len;
	t_size	i;

	if (!s1)
		return (NULL);
	len = 0;
	while (len < n && s1[len])
		len++;
	dup = fn_malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
