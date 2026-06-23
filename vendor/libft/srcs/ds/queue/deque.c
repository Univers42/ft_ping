/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:39:27 by marvin            #+#    #+#             */
/*   Updated: 2026/01/23 18:27:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ft_queue.h"

/* Clone proto into ret (allocates). */
void	deque_clone(void *vret, const void *vproto)
{
	const t_deque	*proto = (const t_deque *)vproto;
	t_deque			*ret;

	ret = (t_deque *)vret;
	if (!deque_init(ret, (int)proto->cap, proto->elem_size))
		return ;
	if (proto->len == 0)
		return ;
	ret->len = proto->len;
	ret->start = 0;
	ret->end = ret->len - 1;
	memcpy(ret->buff, proto->buff, proto->len * proto->elem_size);
	return ;
}

/* Free elements with user callback (if provided),
free buffer and reset struct. */
void	deque_destroy(void *vret, void (*free_elem)(void *))
{
	t_deque			*ret;
	size_t			i;
	void			*el;

	ret = (t_deque *)vret;
	if (ret == NULL)
		return ;
	if (free_elem != NULL && ret->buff != NULL && ret->cap != 0)
	{
		i = -1;
		while (++i < ret->len)
		{
			el = (char *)ret->buff + ((ret->start + i) % ret->cap)
				* ret->elem_size;
			free_elem(el);
		}
	}
	fn_free(ret->buff);
	*ret = (t_deque){0};
}

/* Clear deque contents but keep allocated buffer.
 * If free_elem != NULL, call it on each element before clearing.
 */
void	deque_clear(void *vret, void (*free_elem)(void *))
{
	t_deque	*ret;
	size_t	i;
	void	*el;

	ret = (t_deque *)vret;
	if (ret == NULL)
		return ;
	if (free_elem != NULL && ret->buff != NULL && ret->cap != 0)
	{
		i = -1;
		while (++i < ret->len)
		{
			el = (char *)ret->buff + ((ret->start + i) % ret->cap)
				* ret->elem_size;
			free_elem(el);
		}
	}
	ret->len = 0;
	ret->start = 0;
	ret->end = 0;
	if (ret->cap != 0)
		ret->end = ret->cap - 1;
}
