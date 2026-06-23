/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:10:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:36:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H

# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include "../../../include/ft_memory.h"
# include "../../../include/ft_debug.h"
# include "../../../include/ft_math.h"

typedef struct s_queue_node
{
	void				*data;
	struct s_queue_node	*next;
}	t_queue_node;

typedef struct s_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
	size_t			size;
}	t_queue;

typedef struct s_deque
{
	size_t	cap;
	size_t	len;
	size_t	start;
	size_t	end;
	size_t	elem_size;
	void	*buff;
}	t_deque;

// Core functions
t_queue	*ft_queue_create(void);
void	ft_queue_destroy(t_queue *queue);
bool	ft_queue_enqueue(t_queue *queue, void *data);
void	*ft_queue_dequeue(t_queue *queue);

// Access functions
void	*ft_queue_front(t_queue *queue);
void	*ft_queue_rear(t_queue *queue);

// Utility functions
size_t	ft_queue_size(t_queue *queue);
bool	ft_queue_is_empty(t_queue *queue);
void	ft_queue_clear(t_queue *queue);

// Advanced functions
void	ft_queue_print_addresses(t_queue *queue);

/* NOTE: change deque API to accept a generic pointer (void *) so callers
   may pass either t_deque* or a wrapper deque_tt* whose first member is
   an t_deque. This preserves existing call sites. */
bool	deque_init(void *ret, int size, size_t elem_size);
void	deque_ensure_space(void *ret);
bool	deque_push_end(void *ret, const void *item);
bool	deque_push_start(void *ret, const void *item);
void	*deque_pop_end(void *ret);
void	*deque_pop_start(void *ret);
void	*deque_idx(void *ret, size_t idx);
void	*deque_peek(void *ret);
void	deque_peek_into(void *ret, void *out);
void	deque_reset(void *ret);
void	deque_clone(void *ret, const void *proto);
void	deque_destroy(void *ret, void (*free_elem)(void *));
void	deque_clear(void *ret, void (*free_elem)(void *));

#endif
