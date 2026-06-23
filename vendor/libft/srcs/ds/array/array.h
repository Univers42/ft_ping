/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:29:20 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:39:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

/* default sizes / flags */
# define ARRAY_DFT_SIZE 1024
# define AS_DISPOSE 0x01

/* index type used in some sources */
typedef size_t	t_arrayind;

/* Array element */
typedef struct s_arr_elem
{
	size_t				ind;
	char				*val;
	struct s_arr_elem	*next;
	struct s_arr_elem	*prev;
}	t_arr_elem;

/* Array header/metadata */
typedef struct s_array
{
	size_t				max_idx;
	size_t				nelem;
	size_t				first_idx;
	size_t				alloc_size;
	struct s_arr_elem	**elements;
	struct s_arr_elem	*head;
	struct s_arr_elem	*lastref;
}	t_arr;

typedef struct s_as_insert_ctx
{
	t_arr		*a;
	t_arr_elem	*start;
	int			direction;
	size_t		idx;
	t_arr_elem	*elem;
}	t_as_insert_ctx;

/* core array management */
t_arr		*array_create(void);
void		array_resize(t_arr *a, size_t newsize);
void		array_flush(t_arr *a);
void		array_dispose(t_arr *a);
void		array_dispose_elements(t_arr_elem **elements);

/* copy / slice */
t_arr		*array_copy(t_arr *a);
t_arr		*array_slice(t_arr *array, t_arr_elem *start, t_arr_elem *end);
t_arr		*array_slice_safe(t_arr *array, size_t start, size_t end);

/* iteration */
void		array_walk(t_arr *a, void *user,
				void (*func)(t_arr_elem *, void *));

/* shifting / pushing */
int			array_shift(t_arr *a, char **out);
t_arr_elem	**array_shift_safe(t_arr *a, int n, int flags);
int			array_rshift(t_arr *a, int n, char *s);
t_arr_elem	*array_unshift_element(t_arr *a);
int			array_shift_element(t_arr *a, char *v);
void		array_push(t_arr *a, char *v);
void		array_pop(t_arr *a);
/* conversions / utilities */
int			array_value_replace(t_arr *a, size_t i, char *v, char **old);

/* element-level operations */
t_arr_elem	*array_create_element(size_t idx, char *value);
t_arr_elem	*array_copy_element(t_arr_elem *ae);
void		array_dispose_element(t_arr_elem *ae);
void		array_element_replace(t_arr_elem *ae, char *v);
int			array_insert(t_arr *a, size_t i, char *v);

/* find / remove / reference */
t_arr_elem	*find_elem_by_index(t_arr *a, size_t idx);
t_arr_elem	*array_remove(t_arr *a, size_t i);
char		*array_reference(t_arr *a, size_t i);

/* metadata accessors */
size_t		array_num_elements(t_arr *a);
size_t		array_max_index(t_arr *a);
size_t		array_first_index(t_arr *a);
size_t		array_alloc_size(t_arr *a);
t_arr_elem	**array_head(t_arr *a);
bool		array_empty(t_arr *a);
/* element helpers */
char		*element_value(t_arr_elem *ae);
size_t		element_index(t_arr_elem *ae);
t_arr_elem	*element_forw(t_arr_elem *ae);
t_arr_elem	*element_back(t_arr_elem *ae);
void		set_element_value(t_arr_elem *ae, char *v);
void		add_before(t_arr_elem *ae, t_arr_elem *elem);
void		add_after(t_arr_elem *ae, t_arr_elem *elem);

/* setters */
void		set_first_index(t_arr *a, size_t i);
void		set_num_elements(t_arr *a, size_t n);
void		set_max_idx(t_arr *a, size_t i);

/* lastref helpers (exposed because multiple files use them) */
t_arr_elem	*lastref(t_arr *a);
t_arr_elem	*lastref_start(t_arr *a, size_t i);
void		set_lastref(t_arr *a, t_arr_elem *e);
void		unset_lastref(t_arr *a);
void		invalidate_lastref(t_arr *a);
bool		is_lastref(t_arr *a);

/* internal helpers that are used across compilation units */
t_arr_elem	*as_get_first_elem(t_arr *a);
int			as_detach_and_extract(t_arr *a, t_arr_elem *el, char **out);
void		as_renumber_indices(t_arr *a);
int			as_handle_edge_insert(t_arr *a, size_t i, t_arr_elem *elem);
void		as_choose_start_direction(t_arr *a, size_t i, t_arr_elem **start,
				int *direction);
int			as_replace_elem_value(t_arr *a, t_arr_elem *ae, t_arr_elem *elem);
int			as_insert_before_and_fix(t_arr *a, t_arr_elem *ae,
				t_arr_elem *elem);
int			as_walk_and_insert(t_as_insert_ctx *ctx);

#endif
