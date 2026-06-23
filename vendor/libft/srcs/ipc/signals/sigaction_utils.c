/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:41:41 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:36:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"
#include <signal.h>
#include <errno.h>
#include <string.h>
#include "ft_memory.h"

void	posix_zero(sigset_t *s)
{
	if (s)
		ft_memset(s, 0, sizeof(*s));
}

void	posix_add(sigset_t *s, int sig)
{
	size_t	word;
	size_t	bit;

	if (!s || sig <= 0 || sig >= NSIG)
		return ;
	word = (size_t)(sig - 1) / (8 * sizeof(unsigned long));
	bit = (size_t)(sig - 1) % (8 * sizeof(unsigned long));
	((unsigned long *)s)[word] |= (1UL << bit);
}

int	posix_ismember(const sigset_t *s, int sig)
{
	size_t	word;
	size_t	bit;

	if (!s || sig <= 0 || sig >= NSIG)
		return (0);
	word = (size_t)(sig - 1) / (8 * sizeof(unsigned long));
	bit = (size_t)(sig - 1) % (8 * sizeof(unsigned long));
	return ((((const unsigned long *)s)[word] >> bit) & 1UL);
}

/* Convert t_sigset mask -> POSIX sigset_t */
void	build_posix_set(t_sigset mask, sigset_t *dst)
{
	int	sig;

	posix_zero(dst);
	sig = 1;
	while (sig < NSIG)
	{
		if (mask & (1U << (sig - 1)))
			posix_add(dst, sig);
		sig++;
	}
}

/* Convert POSIX sigset_t -> t_sigset mask */
void	to_mask(const sigset_t *pset, t_sigset *out)
{
	int			sig;
	t_sigset	mask;

	mask = 0;
	sig = 1;
	while (sig < NSIG)
	{
		if (posix_ismember(pset, sig))
			mask |= (1U << (sig - 1));
		sig++;
	}
	*out = mask;
}
