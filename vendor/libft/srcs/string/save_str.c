/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:51:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 19:53:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

char	*save_str(const char *s)
{
	return (check_null(ft_strdup(s)));
}
