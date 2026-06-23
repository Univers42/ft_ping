/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:54:29 by marvin            #+#    #+#             */
/*   Updated: 2025/12/20 02:54:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

int	safe_alloc(char **token_v, size_t pos, size_t buffer)
{
	size_t	i;

	i = 0;
	token_v[pos] = fn_malloc(buffer);
	if (!token_v[pos])
	{
		while (i < pos)
			fn_free(token_v[i++]);
		fn_free(token_v);
		return (1);
	}
	return (0);
}

int	allocate_and_copy_token(char **tokens,
									char **current_token,
									const char *start,
									size_t len)
{
	char	*token;

	if (safe_alloc(tokens, current_token - tokens, len + 1))
		return (1);
	token = *current_token;
	while (len--)
		*token++ = *start++;
	*token = '\0';
	return (0);
}

int	allocate_and_copy_tokens(char **tokens,
									const char *s,
									char delimiter,
									size_t token_count)
{
	char		**current_token;
	const char	*start;
	size_t		len;

	current_token = tokens;
	while (*s && current_token < tokens + token_count)
	{
		while (*s == delimiter)
			s++;
		start = s;
		while (*s && *s != delimiter)
			s++;
		if (start != s)
		{
			len = s - start;
			if (allocate_and_copy_token(tokens, current_token, start, len))
				return (1);
			current_token++;
		}
	}
	return (0);
}

int	count_segments(const char *str, char delimiter)
{
	size_t	segment;
	int		in_segment;

	segment = 0;
	in_segment = 0;
	while (*str)
	{
		if (*str == delimiter)
			in_segment = 0;
		else if (!in_segment)
		{
			in_segment = 1;
			segment++;
		}
		str++;
	}
	return (segment);
}
