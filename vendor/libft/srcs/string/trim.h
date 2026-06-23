/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:18:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:39:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIM_H
# define TRIM_H

# include <stdbool.h>
# include <ft_string.h>
# include <unistd.h>
# include "ft_ctype.h"
# include "ft_stdlib.h"
# include "ft_stddef.h"

# define TRIM_SPACES 1
# define TRIM_NUMS 2
# define TRIM_RADIX 4

void	advance_ptr(t_addr *ptr, char delimiter);
int		extract_hex(t_addr *ptr, t_addr result);
int		cumul_value(t_addr *ptr, t_addr target);
int		parse_sign(t_addr *ptr);
int		parse_int(t_addr *ptr);

#endif
