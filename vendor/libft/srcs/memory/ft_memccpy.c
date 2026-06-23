/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:31:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/23 00:35:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*s = (const unsigned char *)src;
	unsigned char		*d;
	unsigned char		uc;

	d = (unsigned char *)dst;
	uc = (unsigned char)c;
	while (n--)
	{
		*d = *s;
		if (*s == uc)
			return (d + 1);
		d++;
		s++;
	}
	return (NULL);
}
