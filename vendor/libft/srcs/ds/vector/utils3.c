/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:46:10 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:07:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

size_t	get_elem_size(t_vec *v)
{
	size_t	es;

	if (v == NULL)
		return (1);
	if (v->elem_size != 0)
		es = v->elem_size;
	else
		es = 1;
	if (v->elem_size == 0)
		v->elem_size = 1;
	return (es);
}

size_t	default_base(size_t es)
{
	size_t	base;

	base = 64 / es;
	if (64 % es)
		base += 1;
	if (base == 0)
		base = 1;
	return (base);
}

size_t	compute_new_cap(t_vec *v, size_t es, size_t need)
{
	size_t	new_cap;

	if (v->cap == 0)
		new_cap = default_base(es);
	else
		new_cap = v->cap * 2;
	while (new_cap < v->len + need)
		new_cap = new_cap * 2 + 1;
	return (new_cap);
}

bool	realloc_to(t_vec *v, size_t new_cap, size_t es)
{
	void	*new_buff;

	new_buff = fn_realloc(v->ctx, new_cap * es);
	if (new_buff == NULL)
		return (false);
	v->ctx = new_buff;
	v->cap = new_cap;
	return (true);
}
