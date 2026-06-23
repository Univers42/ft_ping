/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mbrtowc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:53:13 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 15:50:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wctype.h"
#include "wchar.h"
#include "ft_memory.h"
#include "ft_debug.h"
#include "ft_stddef.h"
#include <unistd.h>

wchar_t	asm_codepoint(size_t needed, const unsigned char *s);

/* determine expected sequence length from first byte */
static size_t	detect_needed(unsigned char c)
{
	if (c < 0x80)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (3);
	if ((c & 0xF8) == 0xF0)
		return (4);
	return (1);
}

/* verify continuation bytes; 
returns 0 on ok,
1 on invalid continuation,
2 if not enough bytes */
static int	check_continuation(const unsigned char *s,
								size_t n,
								size_t needed)
{
	size_t	i;

	if (needed > n)
		return (2);
	i = 1;
	while (i < needed)
	{
		if ((s[i] & 0xC0) != 0x80)
			return (1);
		++i;
	}
	return (0);
}

/* write result to pwc if provided */
static void	store_result(wchar_t *pwc,
					const unsigned char *s,
					size_t needed)
{
	if (!pwc)
		return ;
	if (needed == 1)
		*pwc = (wchar_t)s[0];
	else
		*pwc = asm_codepoint(needed, s);
}

size_t	ft_mbrtowc(wchar_t *pwc,
					const char *s,
					size_t n,
					mbstate_t *ps)
{
	unsigned char	c;
	size_t			needed;
	int				check;

	ft_assert(s && n);
	if (ps)
		ft_memset(ps, 0, sizeof(mbstate_t));
	c = (unsigned char)s[0];
	needed = detect_needed(c);
	if (needed == 1)
		return (store_result(pwc, (const unsigned char *)s, 1), 1);
	check = check_continuation((const unsigned char *)s, n, needed);
	if (check == 2)
		return ((size_t) - 2);
	if (check == 1)
		return (store_result(pwc, (const unsigned char *)s, 1), 1);
	return (store_result(pwc, (const unsigned char *)s, needed), needed);
}
