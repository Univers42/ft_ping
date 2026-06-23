/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:31:37 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:50:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

/* Push a single byte (for byte-oriented vectors elem_size==1) */
bool	vec_push_byte(t_vec *v, unsigned char byte)
{
	if (v->elem_size == 0)
		v->elem_size = 1;
	if (!vec_ensure_space(v))
		return (false);
	((unsigned char *)v->ctx)[v->len++] = byte;
	if (v->elem_size == 1 && v->len < v->cap)
		((unsigned char *)v->ctx)[v->len] = '\0';
	return (true);
}

/* Pop element and return pointer into internal buffer
(valid until reallocation). */
void	*vec_pop(t_vec *v)
{
	ft_assert(v->len > 0);
	v->len--;
	return ((char *)v->ctx + v->len * v->elem_size);
}

/* Return pointer to element at idx. */
void	*vec_idx(t_vec *v, size_t idx)
{
	ft_assert(idx < v->len);
	return ((char *)v->ctx + idx * v->elem_size);
}

/* Provide vec_ctx_idx used by other modules (same as vec_idx) */
void	*vec_ctx_idx(t_vec *v, size_t idx)
{
	return (vec_idx(v, idx));
}
