/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/10 20:58:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <stdlib.h>
#include <stdbool.h>

/* Track the address span of all chunk memory so slab_free() can reject
   non-slab pointers with a single bounds check before any deref. */
static void	slab_track_bounds(t_slab_allocator *slab, t_slab_chunk *chunk,
				size_t bsz)
{
	char	*end;

	end = chunk->memory + chunk->total_blocks * bsz;
	if (slab->lo == NULL || chunk->memory < slab->lo)
		slab->lo = chunk->memory;
	if (end > slab->hi)
		slab->hi = end;
}

/* Return a chunk of `cache` that has a free block, creating (and bounds-
   tracking) a fresh chunk when every existing one is full. */
static t_slab_chunk	*slab_ready_chunk(t_slab_allocator *slab,
						t_slab_cache *cache)
{
	t_slab_chunk	*chunk;
	size_t			bsz;

	chunk = cache->chunks;
	while (chunk != NULL && chunk->free_list == NULL)
		chunk = chunk->next;
	if (chunk != NULL)
		return (chunk);
	chunk = create_slab_chunk(cache);
	if (chunk == NULL)
		return (NULL);
	cache->chunks = chunk;
	bsz = sizeof(t_slab_block) + cache->block_size;
	slab_track_bounds(slab, chunk, bsz);
	return (chunk);
}

void	*slab_alloc(t_slab_allocator *slab, size_t size)
{
	t_slab_cache	*cache;
	t_slab_chunk	*chunk;
	t_slab_block	*block;

	if (slab == NULL)
		return (NULL);
	cache = find_best_cache(slab, size);
	if (cache == NULL)
		return (fn_malloc(size));
	chunk = slab_ready_chunk(slab, cache);
	if (chunk == NULL)
		return (NULL);
	block = chunk->free_list;
	chunk->free_list = block->next;
	block->is_free = false;
	chunk->used_blocks += 1;
	cache->total_allocated += 1;
	return (block->data);
}
