/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:06:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/21 17:20:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_memory.h"
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

void	*fn_realloc3(void *ptr, size_t old_cap, size_t new_cap)
{
	void	*tmp;
	size_t	select_size;

	if (new_cap == 0)
		return (fn_free(ptr), NULL);
	tmp = fn_malloc(new_cap);
	if (!tmp)
		return (NULL);
	if (ptr && old_cap)
	{
		select_size = old_cap;
		if (new_cap < old_cap)
			select_size = new_cap;
		ft_memmove(tmp, ptr, select_size);
	}
	fn_free(ptr);
	return (tmp);
}
