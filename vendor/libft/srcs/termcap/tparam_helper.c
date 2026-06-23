/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tparam_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:04:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:02:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

void	append_char(char **op, char c)
{
	*(*op)++ = c;
}

void	out_dec_width(char **op, int v, int w)
{
	if (w == 3 && v > 999)
		append_char(op, (v / 1000) + '0');
	if (w >= 3)
		append_char(op, (v / 100) % 10 + '0');
	if (w >= 2)
		append_char(op, (v / 10) % 10 + '0');
	append_char(op, (v % 10) + '0');
}

char	*grow(char *base, char **op, int *cap)
{
	int		used;
	char	*nb;

	used = *op - base;
	nb = (char *)xfn_realloc(base, *cap, *cap * 2);
	*op = nb + used;
	return (nb);
}

void	op_swap(int *a, int *b)
{
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

void	op_arith(int *a0, const char **fmt, int *args)
{
	int	val;
	int	op;

	op = (*fmt)[0];
	if ((*fmt)[1] == 'p')
		val = args[(((*fmt)[2]) & 0177) - 0100];
	else
		val = ((*fmt)[2]) & 0177;
	if (op == '-')
		*a0 -= val;
	else if (op == '+')
		*a0 += val;
	else if (op == '*')
		*a0 *= val;
	else if (op == '/')
	{
		if (val)
			*a0 /= val;
		else
			*a0 = 1;
	}
	else
		*a0 = val;
	*fmt += 3;
}
