/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:44:45 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:48:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

/* Initialize hash table with given capacity. */
bool	hash_init(t_hash *h, size_t capacity)
{
	*h = (t_hash){0};
	if (capacity == 0)
		capacity = 64;
	h->elem_size = sizeof(t_hash_entry);
	h->ctx = fn_calloc(capacity, sizeof(t_hash_entry));
	if (h->ctx == NULL)
		return (false);
	h->cap = capacity;
	h->len = 0;
	return (true);
}

/* Simple hash function for strings. */
size_t	hash_func(const char *key, size_t cap)
{
	size_t	hash;

	hash = 5381;
	while (*key)
		hash = ((hash << 5) + hash) + (unsigned char)*key++;
	return (hash % cap);
}

/* Find entry by key. Returns index or -1 if not found. */
int	hash_find_idx(t_hash *h, const char *key)
{
	size_t			idx;
	size_t			i;
	t_hash_entry	*buff;
	char			*del;

	buff = (t_hash_entry *)h->ctx;
	if (h->cap == 0 || key == NULL)
		return (-1);
	del = hash_deleted_key();
	idx = hash_func(key, h->cap);
	i = -1;
	while (++i < h->cap)
	{
		if (buff[idx].key == NULL)
			return (-1);
		if (buff[idx].key != del && strcmp(buff[idx].key, key) == 0)
			return ((int)idx);
		idx = (idx + 1) % h->cap;
	}
	return (-1);
}

/* Sentinel key marking a deleted slot (tombstone): keeps probe chains intact
   for lookups while being reusable by inserts and ignored by destroy/resize. */
char	*hash_deleted_key(void)
{
	static char	deleted;

	return (&deleted);
}

/* Remove an entry: tombstone its slot, return the stored value to free. */
void	*hash_del(t_hash *h, const char *key)
{
	int		idx;
	void	*val;

	idx = hash_find_idx(h, key);
	if (idx < 0)
		return (NULL);
	val = ((t_hash_entry *)h->ctx)[idx].value;
	fn_free(((t_hash_entry *)h->ctx)[idx].key);
	((t_hash_entry *)h->ctx)[idx].key = hash_deleted_key();
	((t_hash_entry *)h->ctx)[idx].value = NULL;
	if (h->len > 0)
		h->len--;
	return (val);
}
