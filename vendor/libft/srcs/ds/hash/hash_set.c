/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:51:08 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:53:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "ft_string.h"

/* validate parameters */
static bool	validate_input(t_hash *h, const char *key)
{
	if (h->cap == 0 || key == NULL)
		return (false);
	return (true);
}

/* grow table when load factor reached */
static bool	ensure_capacity(t_hash *h)
{
	if (h->len >= h->cap / 2)
	{
		if (!hash_resize(h))
			return (false);
	}
	return (true);
}

/* probe for either empty slot or matching key
   returns 1 -> empty slot index in *out
		   2 -> matching key index in *out
		   0 -> table full / not found within capacity */
static int	probe_slot(t_hash *h, size_t start, const char *key, size_t *out)
{
	size_t			i;
	size_t			idx;
	t_hash_entry	*buff;

	buff = (t_hash_entry *)h->ctx;
	idx = start;
	i = 0;
	while (i < h->cap)
	{
		if (buff[idx].key == NULL)
		{
			*out = idx;
			return (1);
		}
		if (strcmp(buff[idx].key, key) == 0)
		{
			*out = idx;
			return (2);
		}
		idx = (idx + 1) % h->cap;
		++i;
	}
	return (0);
}

/* Insert a new entry at slot */
static bool	insert_at(t_hash *h, size_t idx, const char *key, void *value)
{
	t_hash_entry	*buff;

	buff = (t_hash_entry *)h->ctx;
	buff[idx].key = (char *)key;
	buff[idx].value = value;
	h->len++;
	return (true);
}

/* public API: insert or update. The table OWNS its keys: a new insert stores a
   private ft_strdup copy (freed by hash_del/hash_destroy), so callers may pass
   stack/temporary keys safely. Updates keep the existing copy. */
bool	hash_set(t_hash *h, const char *key, void *value)
{
	size_t	slot;
	int		pr;
	char	*copy;

	if (!validate_input(h, key))
		return (false);
	if (!ensure_capacity(h))
		return (false);
	pr = probe_slot(h, hash_func(key, h->cap), key, &slot);
	if (pr == 0)
		return (false);
	if (pr == 2)
		return (((t_hash_entry *)h->ctx)[slot].value = value, true);
	copy = ft_strdup(key);
	if (!copy)
		return (false);
	return (insert_at(h, slot, copy, value));
}
