/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:36:29 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/19 02:55:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"

char	str_pop(void)
{
	char		ret;
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	ft_assert(v->len > 0);
	ret = v->buff[--v->len];
	v->buff[v->len] = 0;
	return (ret);
}

char	dyn_str_pop(t_dyn_str *s)
{
	char	ret;

	ft_assert(s != NULL && s->len > 0);
	ret = s->buff[--s->len];
	s->buff[s->len] = 0;
	return (ret);
}
