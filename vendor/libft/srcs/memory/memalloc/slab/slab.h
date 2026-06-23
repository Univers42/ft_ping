/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slab.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:26:42 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 20:29:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLAB_H
# define SLAB_H

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_SLAB_SIZES 8

/* Stamped into every slab block so slab_free() can recognise a slab pointer in
   O(1) (after a cheap bounds check) and route it via block->chunk, instead of
   scanning every cache/chunk. Non-slab pointers fall back to libc free. */
# define SLAB_MAGIC 0x5742534C41425F31UL

typedef struct s_slab_block
{
	struct s_slab_block	*next;
	struct s_slab_chunk	*chunk;
	size_t				magic;
	bool				is_free;
	char				data[];
}						t_slab_block;

typedef struct s_slab_chunk
{
	struct s_slab_chunk	*next;
	char				*memory;
	size_t				block_size;
	size_t				used_blocks;
	size_t				total_blocks;
	t_slab_block		*free_list;
}						t_slab_chunk;

typedef struct s_slab_cache
{
	size_t			block_size;
	size_t			blocks_per_chunk;
	size_t			total_allocated;
	size_t			total_freed;
	t_slab_chunk	*chunks;
}					t_slab_cache;

typedef struct s_slab_allocator
{
	t_slab_cache	caches[MAX_SLAB_SIZES];
	size_t			cache_count;
	char			*lo;
	char			*hi;
}					t_slab_allocator;

void			slab_init(t_slab_allocator *slab);
void			slab_add_cache(t_slab_allocator *slab, size_t block_size,
					size_t blocks_per_chunk);
void			*slab_alloc(t_slab_allocator *slab, size_t size);
void			slab_free(t_slab_allocator *slab, void *ptr);
void			slab_destroy(t_slab_allocator *slab);
void			slab_stats(t_slab_allocator *slab);
t_slab_chunk	*create_slab_chunk(t_slab_cache *cache);
t_slab_cache	*find_best_cache(t_slab_allocator *slab, size_t size);
t_slab_block	*slab_get_block_at_ptr(t_slab_chunk *chunk,
					t_slab_cache *cache, void *ptr);			
#endif
