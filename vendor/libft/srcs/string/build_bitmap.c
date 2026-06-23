/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bitmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:35:33 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:44:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

void	build_bitmap32(uint32_t bm[BYTE], const char *pattern)
{
	size_t			i;
	unsigned char	uc;

	if (!bm)
		return ;
	i = -1;
	while (++i < BYTE)
		bm[i] = 0;
	if (!pattern)
		return ;
	while (*pattern)
	{
		uc = (unsigned char)*pattern++;
		bm[uc >> 5] |= (1u << (uc & 31));
	}
}

int	bitmap32_has(const uint32_t bm[BYTE], unsigned char c)
{
	return ((bm[c >> 5] & (1u << (c & 31))) != 0);
}

void	bitmap32_set(uint32_t bm[BYTE], unsigned char c)
{
	bm[c >> 5] |= (1u << (c & 31));
}

void	bitmap32_zero(uint32_t bm[BYTE])
{
	ft_memset(bm, 0, BYTE * sizeof(uint32_t));
}
