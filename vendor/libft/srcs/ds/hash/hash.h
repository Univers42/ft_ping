/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:39:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "../../../include/ds.h"
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>

typedef struct s_hash_entry
{
	char	*key;
	void	*value;
}	t_hash_entry;

typedef struct s_vec	t_hash; // ctx holds t_hash_entry

bool	hash_init(t_hash *h, size_t capacity);
size_t	hash_func(const char *key, size_t cap);
int		hash_find_idx(t_hash *h, const char *key);
bool	hash_resize(t_hash *h);
bool	hash_set(t_hash *h, const char *key, void *value);
void	*hash_get(t_hash *h, const char *key);
void	*hash_del(t_hash *h, const char *key);
char	*hash_deleted_key(void);
void	hash_destroy(t_hash *h, void (*free_val)(void *));

#endif