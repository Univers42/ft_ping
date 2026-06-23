/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchrnul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:53:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:39:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchrnul(const char *s, int c)
{
	char	*p;

	p = ft_strchr(s, c);
	if (!p)
		p = (char *)s + ft_strlen(s);
	return (p);
}
