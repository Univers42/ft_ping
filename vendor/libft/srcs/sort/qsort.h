/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:12:38 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/27 16:16:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QSORT_H
# define QSORT_H

# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <stdio.h>
# include <time.h>
# include "ft_memory.h"

# define LOW 0x1
# define HIGH 0x2

typedef struct s_intern
{
	char	*basep;
	size_t	low;
	size_t	high;
	size_t	size;
	int		(*compar)(const void *, const void *);
	char	*tmp;
}	t_intern;

/* ctx used for pushing child ranges (reduce arg count) */
typedef struct s_pushctx
{
	t_intern	*stack;
	size_t		*sp;
	size_t		cap;
	t_intern	*cur;
	size_t		p;
}	t_pushctx;

// utils helpers
void	swap_elems(t_intern *metas, size_t ai, size_t bi);

/* stack helpers */
void	push_children(t_pushctx *ctx);
int		stack_push(t_intern *stack, size_t *sp, size_t cap, t_intern item);

/* recursive helper */
void	qsort_rec(t_intern *metas);

/* partition used by recursive/iterative qsort implementations */
size_t	partition(t_intern *metas);

/* public sorter prototype (used by callers/tests) */
void	ft_qsort(void *base, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *));

#endif
