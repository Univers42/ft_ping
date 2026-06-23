/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:04:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/27 15:49:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memsplit.h"

static void	*copy_part(t_split_info *info, size_t start, size_t end)
{
	void	*part;
	size_t	size;
	uint8_t	*src_pos;

	size = (end - start) * info->elem_size;
	if (size == 0)
		return (NULL);
	part = fn_malloc(size);
	if (!part)
		return (NULL);
	src_pos = info->src + (start * info->elem_size);
	memcpy(part, src_pos, size);
	return (part);
}

/* free all allocated parts and the parts array itself using the singleton */
static void	free_parts(size_t count)
{
	t_memsplit_part	*parts;
	size_t			i;

	parts = res_singleton(NULL);
	if (!parts)
		return ;
	i = -1;
	while (++i < count)
		fn_free(parts[i].data);
	fn_free(parts);
	res_singleton(NULL);
}

static int	add_split_part(size_t *idx, t_split_info *info,
				size_t start, size_t end)
{
	t_memsplit_part	*res;
	void			*part;
	size_t			size;

	res = res_singleton(NULL);
	if (!res)
		return (0);
	part = copy_part(info, start, end);
	if (!part && start != end)
		return (0);
	if (part)
	{
		size = (end - start) * info->elem_size;
		res[*idx].data = part;
		res[*idx].size = size;
		(*idx)++;
	}
	return (1);
}

static size_t	do_split(t_memsplit_part *res, t_split_info *info)
{
	size_t	i;
	size_t	start;
	size_t	count;
	uint8_t	*pos;

	(void)res;
	i = 0;
	start = 0;
	count = 0;
	while (i < info->elem_count)
	{
		pos = info->src + (i * info->elem_size);
		if (memcmp(pos, info->delim, info->elem_size) == 0)
		{
			if (!add_split_part(&count, info, start, i))
				return (free_parts(count), 0);
			start = i + 1;
		}
		i++;
	}
	if (!add_split_part(&count, info, start, info->elem_count))
		return (free_parts(count), 0);
	return (count);
}

t_memsplit_part	*memsplit(void *src, size_t total, size_t elem, void *delim)
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
	result = fn_malloc((delim_cnt + 2) * sizeof(t_memsplit_part));
	if (!result)
		return (NULL);
	res_singleton(result);
	final_cnt = do_split(result, &info);
	if (final_cnt == 0)
		return (NULL);
	result[final_cnt].data = NULL;
	result[final_cnt].size = 0;
	return (result);
}
