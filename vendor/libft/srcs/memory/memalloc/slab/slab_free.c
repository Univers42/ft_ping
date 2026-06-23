/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/05 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <stdlib.h>
#include <stddef.h>

/* O(1) free: a pointer outside the allocator's chunk span is plain libc memory
   (bounds check, no deref). Inside the span, the block header sits at a fixed
   offset; its magic confirms it is really a slab block (an in-span libc pointer
   would not match), and block->chunk gives the freelist to return it to. */
void	slab_free(t_slab_allocator *slab, void *ptr)
{
	t_slab_block	*block;
	t_slab_chunk	*chunk;

	if (slab == NULL || ptr == NULL)
		return ;
	if ((char *)ptr < slab->lo || (char *)ptr >= slab->hi)
	{
		fn_free(ptr);
		return ;
	}
	block = (t_slab_block *)((char *)ptr - offsetof(t_slab_block, data));
	if (block->magic != SLAB_MAGIC)
	{
		fn_free(ptr);
		return ;
	}
	if (block->is_free)
		return ;
	chunk = block->chunk;
	block->is_free = true;
	block->next = chunk->free_list;
	chunk->free_list = block;
	chunk->used_blocks -= 1;
}
