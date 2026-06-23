/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:22:34 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:39:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stdlib.h>
# include <stdbool.h>
# include "../../../include/ft_stddef.h"
# include "../../../include/ft_memory.h"
# include "../../../include/ft_string.h"

typedef struct s_vec
{
	size_t	cap;
	size_t	len;
	size_t	elem_size;
	void	*ctx;
}	t_vec;

bool	vec_init(t_vec *ret);
bool	vec_ensure_space(t_vec *v);
bool	vec_ensure_space_n(t_vec *v, size_t n);
bool	vec_push(t_vec *v, const void *el);
bool	vec_npush(t_vec *v, const void *el, size_t n);
bool	vec_push_nstr(t_vec *v, const char *str, size_t n);
bool	vec_push_str(t_vec *v, const char *str);
bool	vec_push_byte(t_vec *v, unsigned char byte);
void	*vec_pop(t_vec *v);
void	*vec_idx(t_vec *v, size_t idx);
void	*vec_ctx_idx(t_vec *v, size_t idx);
void	vec_append_fd(int fd, t_vec *ret);
void	vec_destroy(t_vec *v, void (*free_elem)(void *));
bool	vec_ends_with_str(t_vec *v, const char *str);
void	vec_clear(t_vec *v);
void	vec_push_char(t_vec *v, char c);
void	vec_push_int(t_vec *v, int n);
size_t	get_elem_size(t_vec *v);
size_t	default_base(size_t es);
size_t	compute_new_cap(t_vec *v, size_t es, size_t need);
bool	realloc_to(t_vec *v, size_t new_cap, size_t es);

#endif
