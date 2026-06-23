/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_null.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:52:35 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 23:12:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include "ft_stdio.h"

#if DEBUG

void	out_of_space(void)
{
	dprintf(STDERR_FILENO, "Out of space\n");
	ft_abort();
}
#else

void	out_of_space(void)
{
	dprintf(STDERR_FILENO, "Out of space");
	exit(ENOMEM);
}

#endif

void	*check_null(void *p)
{
	if (!p)
		out_of_space();
	return (p);
}
