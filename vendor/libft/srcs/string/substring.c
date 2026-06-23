/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:58:32 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 19:58:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	*substring(const char *string, size_t start, size_t end)
{
	size_t	len;
	char	*result;

	len = end - start;
	result = (char *)fn_malloc(len + 1);
	if (!result)
		return ((char *) NULL);
	ft_strncpy(result, string + start, len);
	result[len] = '\0';
	return (result);
}
