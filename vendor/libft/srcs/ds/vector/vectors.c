/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 23:29:26 by marvin            #+#    #+#             */
/*   Updated: 2026/01/09 23:29:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_memory.h"
#include "ft_string.h"

/* Initialize vector (no allocation). */
bool	vec_init(t_vec *ret)
{
	*ret = (t_vec){0};
	ret->elem_size = 1;
	ret->ctx = NULL;
	return (true);
}

/* Push element (copy from `el`). */
bool	vec_push(t_vec *v, const void *el)
{
	if (!vec_ensure_space(v))
		return (false);
	ft_memcpy((char *)v->ctx + v->len * v->elem_size, el, v->elem_size);
	v->len++;
	return (true);
}

bool	vec_npush(t_vec *v, const void *el, size_t n)
{
	if (n == 0)
		return (true);
	if (!vec_ensure_space_n(v, n + (v->elem_size == 1)))
		return (false);
	memcpy((char *)v->ctx + v->len * v->elem_size, el, n * v->elem_size);
	v->len += n;
	if (v->elem_size == 1)
		((char *)v->ctx)[v->len] = '\0';
	return (true);
}

bool	vec_push_nstr(t_vec *v, const char *str, size_t n)
{
	ft_assert(v != NULL && v->elem_size == 1 && str != NULL);
	if (!vec_ensure_space_n(v, n + 1))
		return (false);
	if (n > 0)
		ft_memcpy((char *)v->ctx + v->len, str, n);
	v->len += n;
	((char *)v->ctx)[v->len] = '\0';
	return (true);
}

bool	vec_push_str(t_vec *v, const char *str)
{
	if (str == NULL)
		return (false);
	return (vec_push_nstr(v, str, ft_strlen(str)));
}
