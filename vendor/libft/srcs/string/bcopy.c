/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bcopy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:52:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:17:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"
#include <stdint.h>

static void	forward_byte_copy(const unsigned char *s,
				unsigned char *d, size_t n);
static void	forward_word_copy(const unsigned char **ps,
				unsigned char **pd, size_t *pn);
static void	backward_word_copy(const unsigned char **ps,
				unsigned char **pd, size_t *pn);
static void	backward_byte_copy(const unsigned char *s,
				unsigned char *d, size_t n);

void	bcopy(const void *src, void *dst, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	uintptr_t			s_align;

	if (n == 0 || src == dst)
		return ;
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	if (d < s)
	{
		s_align = (uintptr_t)s | (uintptr_t)d;
		if ((s_align & (sizeof(size_t) - 1)) == 0 && n >= sizeof(size_t))
			forward_word_copy(&s, &d, &n);
		forward_byte_copy(s, d, n);
	}
	else
	{
		s_align = (uintptr_t)s | (uintptr_t)d;
		if ((s_align & (sizeof(size_t) - 1)) == 0 && n >= sizeof(size_t))
			backward_word_copy(&s, &d, &n);
		backward_byte_copy(s, d, n);
	}
}

/*
 * Copy n bytes forward, byte-wise.
 */
static void	forward_byte_copy(const unsigned char *s,
				unsigned char *d, size_t n)
{
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
}

/*
 * Copy n bytes backward, byte-wise.
 */
static void	backward_byte_copy(const unsigned char *s,
								unsigned char *d, size_t n)
{
	s += n;
	d += n;
	while (n > 0)
	{
		s--;
		d--;
		*d = *s;
		n--;
	}
}

/*
 * Copy using size_t words forward when both pointers are aligned.
 * Leaves remaining bytes to be handled by caller.
 */
static void	forward_word_copy(const unsigned char **ps,
					unsigned char **pd, size_t *pn)
{
	size_t	word_count;
	size_t	*sw;
	size_t	*dw;

	word_count = *pn / sizeof(size_t);
	if (word_count == 0)
		return ;
	sw = (size_t *)(uintptr_t)(*ps);
	dw = (size_t *)(uintptr_t)(*pd);
	while (word_count > 0)
	{
		*dw = *sw;
		dw++;
		sw++;
		word_count--;
	}
	*ps = (const unsigned char *)sw;
	*pd = (unsigned char *)dw;
	*pn = *pn % sizeof(size_t);
}

/*
 * Copy using size_t words backward when both pointers are aligned.
 * Leaves remaining bytes to be handled by caller.
 */
static void	backward_word_copy(const unsigned char **ps,
					unsigned char **pd, size_t *pn)
{
	size_t		word_count;
	size_t		*sw;
	size_t		*dw;
	uintptr_t	base_s;
	uintptr_t	base_d;

	word_count = *pn / sizeof(size_t);
	if (word_count == 0)
		return ;
	base_s = (uintptr_t)(*ps + *pn);
	base_d = (uintptr_t)(*pd + *pn);
	sw = (size_t *)base_s;
	dw = (size_t *)base_d;
	while (word_count > 0)
	{
		sw--;
		dw--;
		*dw = *sw;
		word_count--;
	}
	*pn = *pn % sizeof(size_t);
	*ps = (const unsigned char *)sw;
	*pd = (unsigned char *)dw;
}
