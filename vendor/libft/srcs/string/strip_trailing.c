/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_trailing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:50:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/27 21:00:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

/**
 * Remove all trailing whitespaces from STRING. This includes
 * newlines. if newlines only is non-zero, only trainlinng newline
 * are removed. STRING should be terminated with a zero
 */
void	strip_trailing(char *string, int len, bool nl_only)
{
	while (len >= 0)
	{
		if ((nl_only && string[len] == '\n')
			|| (!nl_only && ft_isspace(string[len])))
			len--;
		else
			break ;
		string[len + 1] = '\0';
	}
}
