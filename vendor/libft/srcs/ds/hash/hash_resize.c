/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_resize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/06/05 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

/* Move one live entry into the grown table, then free its old key copy.
   hash_set re-strdups into new_h (already sized, so it won't recurse). */
static void	rehash_one(t_hash *new_h, t_hash_entry *e)
{
	hash_set(new_h, e->key, e->value);
	fn_free(e->key);
}

/* Resize hash table and rehash entries. */
bool	hash_resize(t_hash *h)
{
	t_hash			new_h;
	size_t			i;
	t_hash_entry	*buff;

	buff = (t_hash_entry *)h->ctx;
	if (!hash_init(&new_h, h->cap * 2))
		return (false);
	i = -1;
	while (++i < h->cap)
		if (buff[i].key != NULL && buff[i].key != hash_deleted_key())
			rehash_one(&new_h, &buff[i]);
	fn_free(h->ctx);
	*h = new_h;
	return (true);
}
