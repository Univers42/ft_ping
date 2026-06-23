/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 23:36:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/19 02:51:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"

int	str_init(t_dyn_str *ret)
{
	if (ret)
	{
		*ret = (t_dyn_str){0};
		get_dyn_str(ret);
	}
	else
		get_dyn_str(NULL);
	return (0);
}

int	dyn_str_init(t_dyn_str *s)
{
	ft_assert(s != NULL);
	*s = (t_dyn_str){0};
	return (ST_OK);
}

void	str_init_alloc(void)
{
	t_dyn_str	*v;

	str_init(NULL);
	v = get_dyn_str(NULL);
	str_push('\0');
	v->len--;
}

void	dyn_str_init_alloc(t_dyn_str *str)
{
	dyn_str_init(str);
	dyn_str_push(str, '\0');
	str->len--;
}
