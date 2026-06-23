/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:14:45 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2026/01/23 16:18:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "ft_memory.h"
#include "ft_string.h"
#define START 0
#define END 1

// #include "TDD/test.h"

int	safe_alloc(char **token_v, size_t pos, size_t buffer);
int	allocate_and_copy_token(char **tokens,
		char **current_token,
		const char *start,
		size_t len);
int	allocate_and_copy_tokens(char **tokens,
		const char *s,
		char delimiter,
		size_t token_count);
int	count_segments(const char *str, char delimiter);

/**
 * @description:
 * Allocates (with fn_malloc, the allocator switch) and returns an array of
 * strings obtained by splitting 's' using the character 'c' as a delimiter
 * The array must end with a NULL pointer
 * @param s pointer to the first character of a string
 * @param c character delimiter is to be the reference for the split
 * @return a new multidimensional array of characters, NULL if faulty
 */

#ifdef SPLIT_OPT

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (!s)
		return (NULL);
	tokens = count_segments(s, c);
	token_v = fn_malloc((tokens + 1) * sizeof(char *));
	if (!token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (allocate_and_copy_tokens(token_v, s, c, tokens))
		return (fn_free(token_v), NULL);
	return (token_v);
}
#else

char	**ft_split(char const *str, char c)
{
	char		**out;
	int			i;
	int			occ;
	int			track[2];
	const char	sep[2] = {c, '\0'};

	out = xfn_calloc((num_blocks(str, (char *)sep) + 1), sizeof(char *));
	if (out == 0)
		return (0);
	i = 0;
	occ = 0;
	while (str[i] != 0)
	{
		track[START] = find_block(&track[END], str + i, (char *)sep);
		if (track[START] == -1)
			return (out);
		out[occ] = fn_malloc(track[END] - track[START] + 1);
		if (out[occ] == 0)
			return (free_list((void **)out, occ), NULL);
		ft_strlcpy(out[occ++], str + i + track[START],
			track[END] - track[START] + 1);
		i += track[END];
	}
	return (out);
}

char	**ft_split_str(char *str, char *sep)
{
	char		**out;
	int			i;
	int			occ;
	int			track[2];

	out = xfn_calloc((num_blocks(str, sep) + 1), sizeof(char *));
	if (out == 0)
		return (0);
	i = 0;
	occ = 0;
	while (str[i] != 0)
	{
		track[START] = find_block(&track[END], str + i, sep);
		if (track[START] == -1)
			return (out);
		out[occ] = fn_malloc(track[END] - track[START] + 1);
		if (out[occ] == 0)
			return (free_list((void **)out, occ), NULL);
		ft_strlcpy(out[occ++], str + i + track[START],
			track[END] - track[START] + 1);
		i += track[END];
	}
	return (out);
}

#endif
