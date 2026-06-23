/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:37:04 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:04:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	needle_len;
	size_t	i;

	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i])
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

static int	nstr_match(const char *h, const char *needle, t_size remaining)
{
	while (*h && *needle && *h == *needle && remaining > 0)
	{
		h++;
		needle++;
		remaining--;
	}
	return (*needle == '\0');
}

char	*ft_strnstr(const char *haystack, const char *needle, t_size n)
{
	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && n > 0)
	{
		if (nstr_match(haystack, needle, n))
			return ((char *)haystack);
		n--;
		haystack++;
	}
	return (NULL);
}
