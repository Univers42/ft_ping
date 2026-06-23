/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_spe_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:42:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:37:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

bool	is_spechr(int c)
{
	const char	*spec = ";$'\"<>|&()\n";

	if (ft_strchr(spec, c) || ft_isspace(c))
		return (true);
	return (false);
}
