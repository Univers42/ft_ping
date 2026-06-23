/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_leading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:44:29 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:15:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "ft_string.h"
#include "ft_ctype.h"
#include "ft_debug.h"

void	strip_leading(char *string)
{
	char	*start;
	size_t	len;

	start = string;
	while (*string && (ft_isspace(*string) || *string == '\n'))
		string++;
	if (string != start)
	{
		len = ft_strlen(string);
		ft_strncpy(string, start, len);
		start[len] = '\0';
	}
}

void	trim_newline(char *s)
{
	if (!s)
		return ;
	s[strcspn(s, "\r\n")] = '\0';
}

static size_t	substr_trail(int flags, const char *pattern, char *line)
{
	size_t	len;
	size_t	plen;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (!pattern || pattern[0] == '\0' || !(flags & SKIP_TRIM_SUBSTR))
		return (len);
	{
		plen = ft_strlen(pattern);
		if (plen == 0 || plen > len)
			return (len);
		while (len >= plen)
		{
			if (memcmp(line + len - plen, pattern, plen) == 0)
			{
				len -= plen;
				line[len] = '\0';
			}
			else
				break ;
		}
	}
	return (len);
}

/* Remove trailing characters/substrings according to flags.
 * - If pattern == NULL or empty, no-op.
 * - Flags:
 *   SKIP_TRIM_CHARS  :
 * treat pattern as set of chars; trim any trailing run of those chars
 *   SKIP_TRIM_SUBSTR :
 * treat pattern as whole substring; remove repeated
 * 	occurrences of the substring at the end
 *   SKIP_TRIM_WORDS  :
 * treat pattern as separator set and
 * remove trailing separators (alias of CHARS)
 * Returns the original pointer 'line' (modified in-place).
 */
char	*skip_trailing_flags(char *line, const char *pattern, int flags)
{
	size_t	len;

	ft_assert(line != NULL);
	len = substr_trail(flags, pattern, line);
	if ((flags & SKIP_TRIM_CHARS) || (flags & SKIP_TRIM_WORDS))
	{
		if (!pattern)
			return (line);
		while (len > 0
			&& ft_strchr(pattern, (unsigned char)line[len - 1]) != NULL)
		{
			len--;
			line[len] = '\0';
		}
	}
	return (line);
}

/* Convenience wrapper: default behavior treats pattern as character set */
char	*skip_trailing(char *line, const char *pattern_to_skip)
{
	return (skip_trailing_flags(line, pattern_to_skip, SKIP_TRIM_CHARS));
}
