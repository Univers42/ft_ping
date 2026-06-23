/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memsplit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:22:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/27 15:46:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memsplit.h"

#define MEMSPLIT_MAX_PARTS 1024

t_memsplit_part	*fetch_split_part(void)
{
	static t_memsplit_part	stack_parts[MEMSPLIT_MAX_PARTS];

	return (stack_parts);
}

void	memsplit_free(t_memsplit_part *parts, size_t n)
{
	size_t	i;

	if (!parts)
		return ;
	i = 0;
	while (i < n)
	{
		fn_free(parts[i].data);
		parts[i].data = NULL;
		parts[i].size = 0;
		i++;
	}
	if (parts != fetch_split_part())
		fn_free(parts);
}

size_t	memsplit_count(t_memsplit_part *parts)
{
	size_t	count;

	if (!parts)
		return (0);
	count = 0;
	while (parts[count].data)
		count++;
	return (count);
}

size_t	count_delims(t_split_info *info)
{
	size_t	i;
	size_t	count;
	uint8_t	*pos;

	i = 0;
	count = 0;
	while (i < info->elem_count)
	{
		pos = info->src + (i * info->elem_size);
		if (memcmp(pos, info->delim, info->elem_size) == 0)
			count++;
		i++;
	}
	return (count);
}
