/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:14:02 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:17:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.h"

/* Pop element from start. 
Returns pointer into internal buffer (valid until next reallocation). */
void	*deque_pop_start(void *vret)
{
	t_deque	*ret;
	void	*src;

	ret = (t_deque *)vret;
	ft_assert(ret->len > 0);
	src = (char *)ret->buff + ret->start * ret->elem_size;
	ret->start = (ret->start + 1) % ret->cap;
	ret->len--;
	return (src);
}

/* Index into deque; returns pointer into internal buffer. */
void	*deque_idx(void *vret, size_t idx)
{
	t_deque	*ret;

	ret = (t_deque *)vret;
	ft_assert(idx < ret->len);
	return ((char *)ret->buff + ((ret->start + idx)
			% ret->cap) * ret->elem_size);
}

void	*deque_peek(void *vret)
{
	return (deque_idx(vret, 0));
}

void	deque_peek_into(void *vret, void *out)
{
	t_deque	*ret;

	ret = (t_deque *)vret;
	ft_assert(ret != NULL && out != NULL);
	memcpy(out, deque_idx(ret, 0), ret->elem_size);
}

void	deque_reset(void *vret)
{
	t_deque	*ret;

	ret = (t_deque *)vret;
	if (!ret)
		return ;
	ret->start = 0;
	ret->len = 0;
	if (ret->cap == 0)
		ret->end = 0;
	else
		ret->end = (ret->cap - 1);
}
