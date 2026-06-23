/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab_get_block_at_ptr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:14:08 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 20:19:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slab.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define START 0
#define PTR 1

t_slab_block	*slab_get_block_at_ptr(t_slab_chunk *chunk,
									t_slab_cache *cache, void *ptr)
{
	char			*start;
	size_t			bsz;
	size_t			offset;
	uintptr_t		p[2];
	t_slab_block	*blk;

	start = chunk->memory;
	bsz = sizeof(t_slab_block) + cache->block_size;
	p[START] = (uintptr_t)start;
	p[PTR] = (uintptr_t)ptr;
	if (p[PTR] < p[START] || p[PTR] >= p[START] + chunk->total_blocks * bsz)
		return (NULL);
	offset = (size_t)((p[PTR] - p[START]) / bsz);
	blk = (t_slab_block *)(p[START] + offset * bsz);
	if (blk->data != ptr)
		return (NULL);
	return (blk);
}
