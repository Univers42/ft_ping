/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memsplit_zcopy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:16:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/27 15:45:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memsplit.h"

static void	add_zc_part(size_t *idx, t_split_info *info,
						size_t start, size_t end)
{
	t_memsplit_part	*res;
	size_t			size;

	res = fetch_split_part();
	size = (end - start) * info->elem_size;
	if (size == 0)
		return ;
	res[*idx].data = info->src + (start * info->elem_size);
	res[*idx].size = size;
	(*idx)++;
}

static size_t	do_split_zc(t_split_info *info)
{
	size_t	i;
	size_t	start;
	size_t	count;
	uint8_t	*pos;

	i = 0;
	start = 0;
	count = 0;
	while (i < info->elem_count)
	{
		pos = info->src + (i * info->elem_size);
		if (memcmp(pos, info->delim, info->elem_size) == 0)
		{
			add_zc_part(&count, info, start, i);
			start = i + 1;
		}
		i++;
	}
	add_zc_part(&count, info, start, info->elem_count);
	return (count);
}

t_memsplit_part	*memsplit_zc(void *src, size_t total, size_t elem, void *delim)
{
	t_split_info	info;
	t_memsplit_part	*result;
	size_t			delim_cnt;
	size_t			final_cnt;

	if (!src || !delim || !total || !elem || elem > total)
		return (NULL);
	info.src = (uint8_t *)src;
	info.elem_size = elem;
	info.elem_count = total / elem;
	info.delim = delim;
	delim_cnt = count_delims(&info);
	if (delim_cnt + 2 > MEMSPLIT_MAX_PARTS)
		return (NULL);
	result = fetch_split_part();
	final_cnt = do_split_zc(&info);
	if (final_cnt == 0)
		return (NULL);
	result[final_cnt].data = NULL;
	result[final_cnt].size = 0;
	return (result);
}
