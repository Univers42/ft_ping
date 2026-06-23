/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:23:44 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 02:56:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ds.h"

bool	is_sep(t_dyn_str *line, char *sep, t_dyn_str *full_file)
{
	const size_t	sep_len = ft_strlen(sep);

	if (full_file->len == 0 || full_file->buff[full_file->len - 1] == '\n')
	{
		if (ft_strcmp(line->buff, sep) == 0)
			return (true);
		else if (line->buff[line->len - 1] == '\n'
			&& sep_len + 1 == line->len
			&& ft_strncmp(line->buff, sep, sep_len) == 0)
			return (true);
	}
	return (false);
}
