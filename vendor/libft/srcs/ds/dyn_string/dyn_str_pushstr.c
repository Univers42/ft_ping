/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_pushstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:36:35 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:15:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"
#include <string.h>
#include "ft_string.h"
#include "ft_debug.h"

int	str_pushstr(const char *s)
{
	return (ft_assert(s != NULL), str_pushnstr(s, ft_strlen(s)));
}

bool	str_check_at(size_t pos, t_ctype fn, const char *cmp, size_t len)
{
	t_dyn_str	*input;

	input = get_dyn_str(NULL);
	ft_assert(input != NULL && input->buff != NULL && pos < input->len);
	if (fn)
		return (fn((unsigned char)str_idx(pos)));
	else
		return (ft_strncmp(input->buff + pos, cmp, len) == 0);
}

bool	dyn_str_check_at(t_dyn_str *s, size_t pos, int (*fn)(int),
					const char *cmp)
{
	ft_assert(s != NULL && s->buff != NULL && pos < s->len);
	if (fn)
		return (fn((unsigned char)s->buff[pos]));
	else
		return (ft_strcmp(s->buff + pos, cmp) == 0);
}
