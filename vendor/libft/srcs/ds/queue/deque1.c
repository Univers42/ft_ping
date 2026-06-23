/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:14:16 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:23:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

/*
 * Initialize deque. If size > 0, allocates backing buffer for `size` elements.
 * Returns true on success.
 */
bool	deque_init(void *vret, int size, size_t elem_size)
{
	t_deque	*ret;

	ret = (t_deque *)vret;
	*ret = (t_deque){0};
	ret->elem_size = elem_size;
	if (size > 0)
	{
		ret->buff = fn_malloc((size_t)size * elem_size);
		if (ret->buff == NULL)
			return (false);
		ret->cap = (size_t)size;
		ret->end = ret->cap - 1;
	}
	return (true);
}

/* Push element at end. `item` points to the source element memory. */
bool	deque_push_end(void *vret, const void *item)
{
	t_deque	*ret;

	ret = (t_deque *)vret;
	deque_ensure_space(ret);
	ft_assert(ret->cap > ret->len || ret->cap != 0);
	if (ret->cap == 0)
		ret->end = 0;
	else
		ret->end = (ret->end + 1) % ret->cap;
	memcpy((char *)ret->buff + ret->end * ret->elem_size,
		item, ret->elem_size);
	ret->len++;
	return (true);
}

/* Push element at start. `item` points to the source element memory. */
bool	deque_push_start(void *vret, const void *item)
{
	t_deque	*ret;

	ret = (t_deque *)vret;
	deque_ensure_space(ret);
	if (ret->len)
		ret->start = ft_smod((int)ret->start - 1, (int)ret->cap);
	else
		ret->start = 0;
	memcpy((char *)ret->buff + ret->start * ret->elem_size,
		item, ret->elem_size);
	ret->len++;
	return (true);
}

/* Pop element from end. Returns pointer into 
internal buffer (valid until next reallocation). */
void	*deque_pop_end(void *vret)
{
	t_deque	*ret;
	void	*src;

	ret = (t_deque *)vret;
	ft_assert(ret->len > 0);
	src = (char *)ret->buff + ret->end * ret->elem_size;
	ret->end = ft_smod((int)ret->end - 1, (int)ret->cap);
	ret->len--;
	return (src);
}
