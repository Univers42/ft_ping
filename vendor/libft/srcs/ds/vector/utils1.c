/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:31:51 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 18:52:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

/* Free elements with user callback (if provided),
free buffer and reset struct. */
void	vec_destroy(t_vec *v, void (*free_elem)(void *))
{
	size_t	i;
	void	*el;

	if (v == NULL)
		return ;
	if (free_elem != NULL && v->ctx != NULL)
	{
		i = -1;
		while (++i < v->len)
		{
			el = (char *)v->ctx + i * v->elem_size;
			free_elem(el);
		}
	}
	fn_free(v->ctx);
	*v = (t_vec){0};
	v->ctx = NULL;
}

bool	vec_ends_with_str(t_vec *v, const char *str)
{
	size_t	str_len;
	size_t	v_len;

	if (!v || !str || v->elem_size != 1)
		return (false);
	str_len = ft_strlen(str);
	v_len = v->len;
	if (str_len > v_len)
		return (false);
	return (ft_strncmp((char *)v->ctx + v_len - str_len,
			str, str_len) == 0);
}

void	vec_clear(t_vec *v)
{
	if (!v)
		return ;
	v->len = 0;
	if (v->ctx && v->elem_size == 1)
		((char *)v->ctx)[0] = '\0';
}

void	vec_push_char(t_vec *v, char c)
{
	if (v->elem_size == 0)
		v->elem_size = 1;
	if (!vec_ensure_space(v))
		return ;
	((char *)v->ctx)[v->len++] = c;
	if (v->elem_size == 1 && v->len < v->cap)
		((char *)v->ctx)[v->len] = '\0';
}

void	vec_push_int(t_vec *v, int n)
{
	if (v->len == 0 && v->elem_size != sizeof(int))
		v->elem_size = sizeof(int);
	if (v->elem_size == 0)
		v->elem_size = sizeof(int);
	if (!vec_ensure_space(v))
		return ;
	*((int *)((char *)v->ctx + v->len * v->elem_size)) = n;
	v->len++;
}
