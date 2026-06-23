/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib_stub4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:45:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 14:56:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strto.h"

uint64_t	ft_strtoull(const char *nptr, char **endptr, int base)
{
	return ((uint64_t)ft_strto(nptr, endptr, base, TYPE_UINT64));
}

uint64_t	ft_strtou64(const char *nptr, char **endptr, int base)
{
	return ((uint64_t)ft_strto(nptr, endptr, base, TYPE_UINT64));
}
