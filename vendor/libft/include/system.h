/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:52:58 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 00:53:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <locale.h>
# include "ft_wctype.h"

//Those functions has to be maybe placed into the libarena implementation
// it's more related to mmemory management, for strings or data structures
typedef union u_smt
{
	int		i;
	char	*cp;
	double	d;
}	t_smt;

typedef struct s_vcs_info
{
	char	*data;
	int		dirty;
	int		ok;
}	t_vcs_info;

// return the size of union - 1. This value is for allocation granurality
static inline size_t	system_size(void)
{
	return (sizeof(t_smt) - 1);
}

static inline void	ensure_locale(void)
{
	static int	done = 0;

	if (!done)
	{
		ft_setlocale(LC_CTYPE, "");
		done = 1;
	}
}

#endif
