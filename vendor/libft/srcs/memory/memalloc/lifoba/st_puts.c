/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:55:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 19:58:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lifoba.h"
#include "ft_string.h"
#include "ft_memory.h"

char	*stnputs(const char *s, size_t n, char *p)
{
	p = make_str_space(n, p);
	p = ft_memcpy(p, s, n);
	return (p);
}

char	*stputs(const char *s, char *p)
{
	return (stnputs(s, ft_strlen(s), p));
}
