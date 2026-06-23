/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:01:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:24:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"
#include "ft_debug.h"

// ...existing code...
int	find_block(int *end, const char *str, const char *sep)
{
	int			i;
	int			prev;
	const int	len = ft_strlen(str);
	int			is_sep;

	i = 0;
	prev = -1;
	ft_assert(len);
	while (i <= len)
	{
		if (sep[1] == '\0')
			is_sep = (str[i] == sep[0]);
		else
			is_sep = (ft_strchr(sep, str[i]) != NULL);
		if (is_sep || !str[i])
		{
			*end = i;
			if ((i - prev) > 1)
				return (prev + 1);
			prev = i;
		}
		i++;
	}
	return (-1);
}

// ...existing code...
int	num_blocks(const char *str, char *sep)
{
	int	i;
	int	occ;
	int	end;
	int	start;

	i = 0;
	occ = 0;
	while (str[i] != 0)
	{
		start = find_block(&end, str + i, sep);
		if (start == -1)
			return (occ);
		occ++;
		i += end;
	}
	return (occ);
}
