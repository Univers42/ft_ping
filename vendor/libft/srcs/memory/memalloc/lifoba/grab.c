/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:32:38 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 20:20:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lifoba.h"
#include <string.h>

void	ungrab_stack_str(void *s)
{
	st_unalloc(s);
}

char	**grab_stack_str(char *p)
{
	char			*base;
	size_t			bytes;
	char			**arr;
	size_t			count;

	base = stack_block();
	if (p >= base)
	{
		bytes = (size_t)(p - base);
		count = bytes / sizeof(char *);
		arr = (char **)arena_malloc((count + 1) * sizeof(char *));
		memcpy(arr, base, count * sizeof(char *));
		arr[count] = NULL;
		return (arr);
	}
	return (NULL);
}

void	grab_stack_block(size_t len)
{
	(void)st_alloc(len);
}
