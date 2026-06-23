/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:30:10 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/06 00:01:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lifoba.h"
#include "ft_memory.h"

void	*arena_malloc(size_t nbytes)
{
	void	*p;

	p = fn_malloc(nbytes);
	return (check_null(p));
}

void	*arena_realloc(void *p, size_t nbytes)
{
	p = fn_realloc(p, nbytes);
	return (check_null(p));
}

void	arena_free(void *p)
{
	fn_free(p);
}
