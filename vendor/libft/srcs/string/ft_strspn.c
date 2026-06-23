/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:07:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:45:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>
#include <stdint.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	uint32_t	bm[8];
	size_t		i;

	if (!s || !accept)
		return (0);
	build_bitmap32(bm, accept);
	i = 0;
	while (s[i] && bitmap32_has(bm, (unsigned char)s[i]))
		++i;
	return (i);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	uint32_t	bm[8];
	size_t		i;

	if (!s || !reject)
		return (0);
	build_bitmap32(bm, reject);
	i = 0;
	while (s[i] && !bitmap32_has(bm, (unsigned char)s[i]))
		++i;
	return (i);
}
