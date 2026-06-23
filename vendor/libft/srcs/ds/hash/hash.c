/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:48:19 by marvin            #+#    #+#             */
/*   Updated: 2026/01/10 00:48:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

/* Get value by key. Returns NULL if not found. */
void	*hash_get(t_hash *h, const char *key)
{
	int				idx;
	t_hash_entry	*buff;

	idx = hash_find_idx(h, key);
	buff = (t_hash_entry *)h->ctx;
	if (idx >= 0)
		return (buff[idx].value);
	return (NULL);
}

/* Free one live entry: its value (via free_val, if given) and its owned key. */
static void	hash_free_entry(t_hash_entry *e, void (*free_val)(void *),
		char *del)
{
	if (e->key == NULL || e->key == del)
		return ;
	if (free_val != NULL)
		free_val(e->value);
	fn_free(e->key);
}

/* Free hash table and reset struct. Frees every owned key; frees values too
   when a free_val is supplied. */
void	hash_destroy(t_hash *h, void (*free_val)(void *))
{
	size_t			i;
	t_hash_entry	*buff;
	char			*del;

	if (h == NULL)
		return ;
	buff = (t_hash_entry *)h->ctx;
	del = hash_deleted_key();
	if (buff != NULL)
	{
		i = -1;
		while (++i < h->cap)
			hash_free_entry(&buff[i], free_val, del);
	}
	fn_free(h->ctx);
	*h = (t_hash){0};
}
