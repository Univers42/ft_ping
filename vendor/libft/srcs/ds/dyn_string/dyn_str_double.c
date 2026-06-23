/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:35:36 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 22:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"
#include <stdlib.h>

void	str_replace_buff(t_dyn_str *v, char *new_buff, size_t new_cap)
{
	ft_assert(v && new_buff);
	new_buff[v->len] = 0;
	fn_free(v->buff);
	v->buff = new_buff;
	v->cap = new_cap;
}

void	dyn_str_replace_buff(t_dyn_str *s, char *new_buff, size_t new_cap)
{
	ft_assert(s && new_buff);
	new_buff[s->len] = 0;
	fn_free(s->buff);
	s->buff = new_buff;
	s->cap = new_cap;
}

int	str_double(void)
{
	char		*tmp;
	size_t		newcap;
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	ft_assert(v != NULL);
	newcap = 64;
	if (v->cap != 0)
		newcap = v->cap * 2;
	tmp = fn_malloc(newcap);
	if (v->buff && v->len)
		memcpy(tmp, v->buff, v->len);
	dyn_str_replace_buff(v, tmp, newcap);
	return (1);
}

int	dyn_str_double(t_dyn_str *s)
{
	size_t	newcap;
	char	*tmp;

	ft_assert(s != NULL);
	newcap = 64;
	if (s->cap)
		newcap = s->cap * 2;
	tmp = fn_malloc(newcap);
	if (s->buff && s->len)
		ft_memcpy(tmp, s->buff, s->len);
	dyn_str_replace_buff(s, tmp, newcap);
	return (1);
}
