/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memsplit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:17:59 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/28 02:56:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMSPLIT_H
# define MEMSPLIT_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

# define MEMSPLIT_MAX_PARTS 1024

typedef struct s_memsplit_part
{
	void	*data;
	size_t	size;
}	t_memsplit_part;

typedef struct s_split_info
{
	uint8_t	*src;
	size_t	elem_size;
	size_t	elem_count;
	void	*delim;
}	t_split_info;

size_t							memsplit_count(t_memsplit_part *parts);
void							memsplit_free(t_memsplit_part *parts, size_t n);
size_t							count_delims(t_split_info *info);
t_memsplit_part					*fetch_split_part(void);

static inline t_memsplit_part	*res_singleton(t_memsplit_part *set)
{
	static t_memsplit_part	*s = NULL;

	if (set != NULL)
		s = set;
	return (s);
}

t_memsplit_part					*memsplit_zc(void *src, size_t total,
									size_t elem, void *delim);
t_memsplit_part					*memsplit(void *src, size_t total,
									size_t elem, void *delim);
#endif
