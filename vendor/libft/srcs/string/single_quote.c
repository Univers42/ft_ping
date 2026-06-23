/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:51:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:52:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_string.h"
#include "quote.h"

static void	choose_quote(const char *s, t_sq_ctx *sq, const char quote);

char	*single_quote(const char *s)
{
	t_sq_ctx	sq;

	sq.p = stack_block();
	while (*s)
	{
		sq.len = ft_strchrnul(s, '\'') - s;
		choose_quote(s, &sq, '\'');
		s += sq.len;
		sq.len = ft_strspn(s, "'");
		if (!sq.len)
			break ;
		choose_quote(s, &sq, '"');
		s += sq.len;
	}
	*sq.p++ = '\0';
	return (stack_block());
}

static void	choose_quote(const char *s, t_sq_ctx *sq, const char quote)
{
	char	*start;

	start = make_str_space(sq->len + 3, sq->p);
	sq->p = start;
	sq->q = start;
	*sq->q++ = quote;
	ft_memcpy(sq->q, s, sq->len);
	sq->q += sq->len;
	*sq->q++ = quote;
	sq->p = sq->q;
}
