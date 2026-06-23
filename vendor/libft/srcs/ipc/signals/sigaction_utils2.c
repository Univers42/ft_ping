/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:35:18 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 19:36:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	posix_zero(sigset_t *s);
void	posix_add(sigset_t *s, int sig);
int		posix_ismember(const sigset_t *s, int sig);
void	build_posix_set(t_sigset mask, sigset_t *dst);
void	to_mask(const sigset_t *pset, t_sigset *out);

t_sig_handler	set_signal_handler(int sig, t_sig_handler handler)
{
	struct sigaction	act;
	struct sigaction	old;
	t_sigset			empty_mask;

	if (sig <= 0 || sig >= NSIG)
		return (SIG_ERR);
	ft_sigemptyset(&empty_mask);
	build_posix_set(empty_mask, &act.sa_mask);
	act.sa_handler = handler;
	act.sa_flags = 0;
	if (sigaction(sig, &act, &old) < 0)
		return (SIG_ERR);
	return (old.sa_handler);
}

// /* BSD-style sigblock implemented via sigprocmask */
// static int sigblock_compat(int newmask)
// {
// 	sigset_t set;
// 	sigset_t oset;
// 	t_sigset mask;

// 	mask = (t_sigset)newmask;
// 	build_posix_set(mask, &set);
// 	if (sigprocmask(SIG_BLOCK, &set, &oset) < 0)
// 		return (-1);
// 	to_mask(&oset, &mask);
// 	return ((int)mask);
// }

/* BSD-style sigsetmask implemented via sigprocmask */
// static int sigsetmask_compat(int newmask)
// {
// 	sigset_t set;
// 	sigset_t oset;
// 	t_sigset mask;

// 	mask = (t_sigset)newmask;
// 	build_posix_set(mask, &set);
// 	if (sigprocmask(SIG_SETMASK, &set, &oset) < 0)
// 		return (-1);
// 	to_mask(&oset, &mask);
// 	return ((int)mask);
// }

/* Real implementation: block/unblock signals and return old mask */
int	ft_sigprocmask(int operation, t_sigset *newset, t_sigset *oldset)
{
	sigset_t			posix_new;
	sigset_t			posix_old;
	sigset_t			*nptr;

	nptr = NULL;
	if (newset)
	{
		build_posix_set(*newset, &posix_new);
		nptr = &posix_new;
	}
	if (sigprocmask(operation, nptr, &posix_old) < 0)
		return (-1);
	if (oldset)
		to_mask(&posix_old, oldset);
	return (0);
}

/* Real implementation: suspend process until a signal arrives */
int	ft_sigsuspend(const t_sigset *set)
{
	sigset_t			posix_set;
	t_sigset			mask;

	mask = 0;
	if (set)
		mask = *set;
	build_posix_set(mask, &posix_set);
	return (sigsuspend(&posix_set));
}
