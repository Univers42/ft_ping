/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_accessors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:17:44 by marvin            #+#    #+#             */
/*   Updated: 2025/12/18 16:17:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dyn_string.h"

void	str_uppdate_len(size_t val)
{
	t_dyn_str	*str;

	str = get_dyn_str(NULL);
	str->len = val;
}

t_dyn_str	*get_dyn_str(t_dyn_str *maybe)
{
	static t_dyn_str	str = {0};

	if (maybe)
		return (maybe);
	return (&str);
}

void	dyn_str_update_pos(t_dyn_str *v, size_t val)
{
	v->pos = val;
}
