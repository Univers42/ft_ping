/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:35:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/19 02:58:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"

/* internal implementation (restore original behavior) */
int	st_push(char el)
{
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	if (v->len + 1 >= v->cap || v->buff == 0)
		if (str_double())
			return (ST_ERR_BASE);
	v->buff[v->len++] = el;
	v->buff[v->len] = 0;
	return (ST_OK);
}

int	str_push(char el)
{
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	if (!v)
		return (ST_ERR_BASE);
	if (!v->buff || v->len + 1 >= v->cap)
		if (!str_double())
			return (ST_ERR_BASE);
	v->buff[v->len++] = el;
	v->buff[v->len] = 0;
	return (ST_OK);
}

int	dyn_str_push(t_dyn_str *s, char el)
{
	ft_assert(s != NULL);
	if (s->len + 1 >= s->cap)
		if (!dyn_str_double(s))
			return (ST_ERR_BASE);
	s->buff[s->len++] = el;
	s->buff[s->len] = 0;
	return (ST_OK);
}
