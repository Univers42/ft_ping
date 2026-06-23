/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:53:18 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 14:31:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEBUG_H
# define FT_DEBUG_H
# include "ft_stddef.h"

void	ft_print_ascii(unsigned char *p, unsigned int size);
void	ft_print_hex(unsigned char *p, unsigned int size, unsigned long addr);
void	*ft_print_memory(void *addr, unsigned int size);
void	*ft_print_array(int *arr, int size, char mode);
void	print_array(int *arr, int size);
void	ft_assert(int cond);
void	debug_todo(const char *message);
int		invalid(const char *msg, int ex);

#endif
