/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_munch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:29:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:14:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <string.h>
#include <stdint.h>
#include "ft_stddef.h"
#include "ft_memory.h"
#include "ft_debug.h"

static char	*fetch_pattern(void *needles, size_t offset,
				size_t size, int idx)
{
	const uintptr_t	addr = (uintptr_t)needles + (idx * size) + offset;
	char			*pat;

	ft_memcpy(&pat, (const void *)addr, sizeof(pat));
	return (pat);
}

int	max_munch(char *haystack, void *needles, size_t offset, size_t size)
{
	int		max_idx;
	int		max_len;
	int		i;
	char	*pattern;

	max_idx = -1;
	max_len = -1;
	i = 0;
	while (ST_SCANNING)
	{
		pattern = fetch_pattern(needles, offset, size, i);
		if (!pattern)
			break ;
		if ((int)ft_strlen(pattern) > max_len
			&& ft_strncmp(pattern, haystack, ft_strlen(pattern)) == 0)
		{
			max_idx = i;
			max_len = (int)ft_strlen(pattern);
		}
		i++;
	}
	return (max_idx);
}
