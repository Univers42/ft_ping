/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:33:18 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 20:02:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include <stdio.h>
#include <string.h>
#include "ft_string.h"

char	*str_save(const char *s)
{
	char	*d;
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_strlen(s) + 1;
	d = (char *)check_null(fn_malloc(n));
	return (ft_memcpy(d, s, n), d);
}
