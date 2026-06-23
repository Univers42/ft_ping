/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_ensure_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:21:54 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:29:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

/* Ensure there's space for one more element, grow if needed. */
static int	need_grow(t_deque *d)
{
	if (d->len < d->cap)
		return (0);
	return (1);
}

static size_t	calc_new_cap(t_deque *d)
{
	size_t	unit;

	if (d->elem_size)
		unit = d->elem_size;
	else
		unit = 1;
	if (d->cap == 0)
		return (64 / unit);
	return (d->cap * 2 + 1);
}

static void	*alloc_new_buff(size_t new_cap, size_t elem_size)
{
	void	*buf;

	buf = fn_malloc(new_cap * elem_size);
	ft_assert(buf != NULL);
	return (buf);
}

static void	copy_elements(t_deque *d, void *new_buff)
{
	size_t	i;
	size_t	src_idx;
	char	*dst;
	char	*src;

	i = -1;
	dst = (char *)new_buff;
	src = (char *)d->buff;
	while (++i < d->len)
	{
		src_idx = (d->start + i) % d->cap;
		memcpy(dst + i * d->elem_size,
			src + src_idx * d->elem_size, d->elem_size);
	}
}

/* main entry */
void	deque_ensure_space(void *vret)
{
	t_deque	*ret;
	size_t	new_cap;
	void	*new_buff;

	ret = (t_deque *)vret;
	if (!need_grow(ret))
		return ;
	new_cap = calc_new_cap(ret);
	new_buff = alloc_new_buff(new_cap, ret->elem_size);
	if (ret->len > 0)
		copy_elements(ret, new_buff);
	fn_free(ret->buff);
	ret->buff = new_buff;
	ret->cap = new_cap;
	ret->start = 0;
	if (ret->len == 0)
		ret->end = 0;
	else
		ret->end = ret->len - 1;
}
