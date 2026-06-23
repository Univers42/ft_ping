/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_idx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:36:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/19 02:53:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"

int	str_idx(size_t idx)
{
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	ft_assert(idx < v->len);
	return (v->buff[idx]);
}

int	dyn_str_idx(t_dyn_str *s, size_t idx)
{
	ft_assert(s && idx < s->len);
	return (s->buff[idx]);
}

int	str_ends_with_str(const char *s)
{
	size_t		sl;
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	ft_assert(v != NULL && v->buff && s);
	sl = ft_strlen(s);
	ft_assert(v->len >= sl);
	if (sl == 0)
		return (1);
	return (ft_memcmp(v->buff + v->len - sl, s, sl) == 0);
}

int	dyn_str_ends_with_str(t_dyn_str *s, const char *suffix)
{
	size_t	sl;

	ft_assert(s != NULL && s->buff && suffix);
	sl = ft_strlen(suffix);
	if (sl == 0)
		return (1);
	if (s->len < sl)
		return (0);
	return (ft_memcmp(s->buff + s->len - sl, suffix, sl) == 0);
}
