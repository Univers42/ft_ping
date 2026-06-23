/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setlocale.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:55:59 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:01:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SETLOCALE_H
# define FT_SETLOCALE_H

# include "ft_wctype.h"
# include <string.h>
# include <stdlib.h>

enum
{
	LOCSIZE = 64
};

typedef struct s_loc
{
	char	locales[FT_CAT_COUNT][LOCSIZE];
	size_t	mb_cur_max;
}	t_loc;

/* function-local static pointer to singleton */
static t_loc	**loc_ptr(void)
{
	static t_loc	*ptr = NULL;

	return (&ptr);
}

int			valid_category(int category);
void		init_store_defaults(t_loc *p);
t_loc		*ensure_store(void);
const char	*find_env_locale(void);
void		update_mb_cur_max(t_loc *store, const char *str);

#endif