/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:38:34 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:40:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "../../include/ft_stddef.h"

typedef struct s_hash_seen
{
	uint32_t	seen[BYTE];
	uint32_t	printed[BYTE];
}	t_hash_seen;

int		bitmap32_has(const uint32_t bm[BYTE], unsigned char c);
void	build_bitmap32(uint32_t bm[BYTE], const char *pattern);
void	bitmap32_set(uint32_t bm[BYTE], unsigned char c);
void	bitmap32_zero(uint32_t bm[BYTE]);
#endif
