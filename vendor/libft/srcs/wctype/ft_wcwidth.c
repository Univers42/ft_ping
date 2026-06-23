/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcwidth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:57:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 02:22:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wctype.h"
#include "wchar.h"

/**
 * lightweight implementation . if we want full implementation
 * we would need data files or compressed tables.
 */
int	ft_wcwidth(wchar_t wc)
{
	if (wc >= 0x20 && wc <= 0x7E)
		return (1);
	if (wc < 0x20 || (wc >= 0x7F && wc <= 0x9F))
		return (-1);
	if ((wc >= 0x0300 && wc <= 0x036F)
		|| (wc >= 0x1AB0 && wc <= 0x1AFF))
		return (0);
	if ((wc >= 0x1100 && wc <= 0x115F)
		|| (wc >= 0x2E80 && wc <= 0xA4CF)
		|| (wc >= 0xAC00 && wc <= 0xD7A3)
		|| (wc >= 0xFF01 && wc <= 0xFF60)
		|| (wc >= 0xFFE0 && wc <= 0xFFE6))
		return (2);
	return (1);
}
