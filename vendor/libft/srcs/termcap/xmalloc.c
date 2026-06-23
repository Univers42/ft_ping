/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 00:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/04 00:02:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"
#include <stdlib.h>
#include <unistd.h>

int	termcap_used_fallback(void)
{
	return (access_glob()->used_fallback);
}

void	termcap_mark_fallback(void)
{
	access_glob()->used_fallback = 1;
}
