/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ensure_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:43:17 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:48:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

/* Ensure there's space for at least one more element. */
bool	vec_ensure_space(t_vec *v)
{
	size_t	es;
	size_t	new_cap;

	if (v == NULL)
		return (false);
	es = get_elem_size(v);
	if (v->ctx != NULL && v->len + 1 <= v->cap)
		return (true);
	new_cap = compute_new_cap(v, es, 1);
	return (realloc_to(v, new_cap, es));
}

bool	vec_ensure_space_n(t_vec *v, size_t n)
{
	size_t	es;
	size_t	new_cap;

	if (v == NULL)
		return (false);
	if (n == 0)
		return (true);
	es = get_elem_size(v);
	if (v->ctx != NULL && v->len + n <= v->cap)
		return (true);
	new_cap = compute_new_cap(v, es, n);
	return (realloc_to(v, new_cap, es));
}
