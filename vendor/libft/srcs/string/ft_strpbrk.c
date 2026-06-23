/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:35:10 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:45:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/* Return pointer to first occurrence in s1 of any byte from s2, or NULL */
char	*ft_strpbrk(const char *s1, const char *s2)
{
	uint32_t	bm[8];
	size_t		i;

	if (!s1 || !s2)
		return (NULL);
	build_bitmap32(bm, s2);
	i = 0;
	while (s1[i])
	{
		if (bitmap32_has(bm, (unsigned char)s1[i]))
			return ((char *)&s1[i]);
		++i;
	}
	return (NULL);
}
