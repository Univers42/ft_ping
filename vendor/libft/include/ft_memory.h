/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:28:23 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:55:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H
# include "ft_stddef.h"
# include "xalloc.h"
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include "../srcs/memory/memalloc/lifoba/lifoba.h"
# include "../srcs/memory/memalloc/pool/pool.h"
# include "../srcs/memory/memalloc/slab/slab.h"
# include "../srcs/memory/memalloc/arena/arena.h"

typedef struct s_mem_tracker
{
	void	**ptrs;
	int		count;
	int		capacity;
}	t_mem_tracker;

void	cleanup_all(t_mem_tracker *tracker);
void	*safe_malloc(t_mem_tracker *tracker, size_t size);
void	init_tracker(t_mem_tracker *tracker);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_swap(void *a, void *b, size_t size);
void	ft_reverse_string(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_print_memory(void *addr, unsigned int size);
void	ft_print_hex(unsigned char *p, unsigned int size, unsigned long addr);
void	ft_print_ascii(unsigned char *p, unsigned int size);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*xfn_malloc(size_t nbytes);
void	*xfn_realloc(void *p, size_t old, size_t newsize);
void	xfn_free(void *ptr);
void	*check_null(void *p);
void	out_of_space(void);
void	*ternary(bool cond, void *true_val, void *false_val);
//int capture_output(const char *cmd, char *buf, size_t cap);
char	*extract_fd(int fd);
void	free_list(void **list, int size);
//void	ast_postorder_traversal_generic(void *vnode, void (*f)(void *node));
//void	ast_postorder_traversal(t_ast_node *node, void (*f)(t_ast_node *node));
void	*xfn_calloc(size_t nmemb, size_t size);
bool	check_overflow(size_t n, size_t size);

/*
** Short aliases so shell call sites read like libc while routing through the
** error-checking wrappers. They switch backend (libc malloc vs ft_malloc) at
** compile time via HAVE_FT_MALLOC, so flipping SAFE swaps every allocation.
** No xrealloc alias: xfn_realloc takes the old size (3-arg), not libc's 2-arg.
*/
# ifndef xmalloc
#  define xmalloc xfn_malloc
# endif
# ifndef xcalloc
#  define xcalloc xfn_calloc
# endif
# ifndef xfree
#  define xfree xfn_free
# endif

static inline void	buffer_destroy(void **to_empty, size_t size)
{
	size_t	i;

	if (!to_empty)
		return ;
	i = -1;
	while (++i < size)
	{
		if (to_empty[i])
			fn_free(to_empty[i]);
	}
	fn_free(to_empty);
}

/**
 * Generic free function:
 * @param data: pointer to the data to free
 * @param count: number of elements in the data
 * @param elem_size: size of each element
 * @param free_elem: function pointer to free each element (can be NULL)
 * 
 * for an array of pointers pass elemt_size as sizeof(void *)
 * and free_elem as the function to free each element
 * for raw buffers that just need a single free pass
 * put -> elem_size as 0 and free_elem as NULL
 * @note `free_any(array_of_pointers, count, sizeof(void *), free)`;
 * @note `free_any(raw_buffer, 1, 0, NULL)`;
 */
static inline void	destroy(void *data, size_t count,
					size_t elem_size, void (*free_elem)(void *))
{
	size_t	i;
	char	*ptr;
	void	*next;
	void	*tmp;

	if (!data)
		return ;
	if (free_elem)
	{
		ptr = (char *)data;
		i = -1;
		while (++i < count)
		{
			ft_memcpy(&tmp, ptr + i * elem_size, sizeof(tmp));
			next = tmp;
			if (next)
				free_elem(next);
		}
	}
	fn_free(data);
}

#endif
