/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 03:37:53 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/27 16:16:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "pipe.h"

/*
 * Grow buf so it holds at least `need` bytes. On realloc failure the OLD buffer
 * stays valid (realloc keeps it) and we return NULL; the single owner
 * (read_line_arena) frees it once — no double free, no leak.
 */
static char	*line_grow(char *buf, size_t *cap, size_t need)
{
	char	*nb;
	size_t	ncap;

	if (need <= *cap)
		return (buf);
	ncap = *cap * 2;
	while (ncap < need)
		ncap *= 2;
	nb = fn_realloc(buf, ncap);
	if (nb)
		*cap = ncap;
	return (nb);
}

/*
 * Read bytes one at a time into the growable buffer until newline or EOF.
 * Returns 1 when a line/data is ready, 0 on immediate EOF (no data),
 * -1 on error. *buf always points to a valid (freeable) buffer on return.
 */
static int	line_fill(int fd, char **buf, size_t *len, size_t *cap)
{
	char	c;
	ssize_t	r;
	char	*nb;

	while (1)
	{
		r = read(fd, &c, 1);
		if (r < 0 && errno == EINTR)
			continue ;
		if (r < 0)
			return (-1);
		if (r == 0)
		{
			if (*len == 0)
				return (0);
			return (1);
		}
		nb = line_grow(*buf, cap, *len + 2);
		if (!nb)
			return (-1);
		*buf = nb;
		(*buf)[(*len)++] = c;
		if (c == '\n')
			return (1);
	}
}

/*
 * Read one line (up to and including '\n') from fd. Returns a NUL-terminated
 * buffer allocated through fn_malloc — the caller frees it with fn_free.
 * Returns NULL on immediate EOF (no data) or error.
 */
char	*read_line_arena(int fd)
{
	char	*buf;
	size_t	len;
	size_t	cap;
	int		r;

	cap = 64;
	len = 0;
	buf = fn_malloc(cap);
	if (!buf)
		return (NULL);
	r = line_fill(fd, &buf, &len, &cap);
	if (r <= 0)
		return (fn_free(buf), NULL);
	buf[len] = '\0';
	return (buf);
}
