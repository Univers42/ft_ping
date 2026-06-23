/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsub.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:19:36 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 16:06:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRSUB_H
# define STRSUB_H

# include <sys/types.h>
# include <stdbool.h>
# include "ft_ctype.h"
# include "ft_string.h"

typedef struct s_subctx
{
	size_t	templen;
	size_t	tempsize;
	size_t	i;
	size_t	patlen;
	char	*temp;
	size_t	repn;
	size_t	remn;
}	t_subctx;

int		append_char(t_subctx *ctx, char ch);
int		append_rest(t_subctx *ctx, const char *string, size_t idx);
int		append_rep(t_subctx *ctx, const char *rep);
char	*ensure_capacity(t_subctx *c, size_t need);
int		handle_match(t_subctx *ctx, const char *string,
			const char *rep, bool glob);
char	*finalize_result(t_subctx *ctx, const char *string);
int		append_c(t_subctx *ctx, char ch);
#endif
