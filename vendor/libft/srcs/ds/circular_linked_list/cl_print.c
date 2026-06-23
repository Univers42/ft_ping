/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/10/21 23:52:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_circular_list.h"
#include "ft_stdio.h"

void	ft_cl_print_addresses(t_circular_list *list)
{
	t_cl_node	*current;
	size_t		i;

	if (!list || ft_cl_is_empty(list))
	{
		ft_printf("Circular List: []\n");
		return ;
	}
	ft_printf("Circular List: [");
	current = list->last->next;
	i = 0;
	while (i < list->size)
	{
		ft_printf("%p", current->data);
		current = current->next;
		i++;
		if (i < list->size)
			ft_printf(" -> ");
	}
	ft_printf(" -> (cycles back)]\n");
}

void	ft_cl_print_n_times(t_circular_list *list, size_t n)
{
	t_cl_node	*current;
	size_t		i;

	if (!list || ft_cl_is_empty(list) || n == 0)
	{
		ft_printf("Circular List (empty or n=0): []\n");
		return ;
	}
	ft_printf("Circular List (%zu cycles): [", n);
	current = list->last->next;
	i = 0;
	while (i < n * list->size)
	{
		ft_printf("%p", current->data);
		current = current->next;
		i++;
		if (i < n * list->size)
			ft_printf(" -> ");
	}
	ft_printf("]\n");
}
