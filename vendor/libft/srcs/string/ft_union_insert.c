/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_union_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:37:21 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/10 21:11:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ds.h"
#include "ft_memory.h"
#include "ft_stdio.h"

void	inter(const char *str1, const char *str2)
{
	t_hash_seen		tab;
	unsigned char	uc;

	if (!str1 || !str2)
		return ;
	ft_memset(&tab, 0, sizeof(tab));
	build_bitmap32(tab.seen, str2);
	while (*str1)
	{
		uc = (unsigned char)*str1;
		if (bitmap32_has(tab.seen, uc) && !bitmap32_has(tab.printed, uc))
		{
			ft_putchar_fd(STDOUT_FILENO, (char)uc);
			tab.printed[uc >> 5] |= (1u << (uc & 31));
		}
		++str1;
	}
}

void	ft_union(const char *str1, const char *str2)
{
	uint32_t		printed[BYTE];
	unsigned char	uc;

	if (!str1 || !str2)
		return ;
	bitmap32_zero(printed);
	while (*str1)
	{
		uc = (unsigned char)*str1++;
		if (!bitmap32_has(printed, uc))
			(ft_putchar_fd(STDOUT_FILENO, (char)uc), bitmap32_set(printed, uc));
	}
	while (*str2)
	{
		uc = (unsigned char)*str2++;
		if (!bitmap32_has(printed, uc))
			(ft_putchar_fd(STDOUT_FILENO, (char)uc), bitmap32_set(printed, uc));
	}
}
