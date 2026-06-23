/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgoto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 00:50:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:07 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

/*
 * parameter string usually wants row (y) first then column (x).
 * Public API: tgoto(cm, hpos, vpos) like classic termcap.
 * We pass (row=vpos, col=hpos) to tparam via an int args[].
 */
char	*tgoto(const char *cm, int hpos, int vpos)
{
	static char	buf[128];
	int			args[4];

	if (!cm)
		return (NULL);
	args[0] = vpos;
	args[1] = hpos;
	args[2] = 0;
	args[3] = 0;
	return (tparam(cm, buf, (int) sizeof(buf), args));
}
