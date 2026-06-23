/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:02:49 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:03:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CTYPE_H
# define FT_CTYPE_H

# include <stdbool.h>

int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isblank(int c);
int		ft_isxdigit(int c);
int		ft_isgraph(int c);
int		hex_digit(char c);
int		is_at_end(int c);
int		assert_char(int in, int expect);
int		is_meta_char(int c);
int		is_word_char(int c);
int		is_name_char(int c);
bool	is_custom_set(int c, const char *set);
int		is_int_name(int c);
bool	is_spechr(int c);
bool	is_escapable(int c);
bool	is_metachar(int c);

#endif
