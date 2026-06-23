/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:25:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 16:21:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"

void	str_clear(void)
{
	t_dyn_str	*v;

	v = get_dyn_str(NULL);
	v->len = 0;
	if (v->buff)
		v->buff[0] = 0;
}

void	dyn_str_clear(t_dyn_str *s)
{
	ft_assert(s != NULL);
	s->len = 0;
	if (s->buff)
		s->buff[0] = 0;
}

void	dyn_str_free(t_dyn_str *s)
{
	if (s && s->buff)
	{
		fn_free(s->buff);
		s->buff = NULL;
		s->cap = 0;
		s->len = 0;
	}
}

void	dyn_str_destroy(t_dyn_str *to_empty)
{
	if (to_empty->buff)
	{
		fn_free(to_empty->buff);
		to_empty->buff = NULL;
	}
}
