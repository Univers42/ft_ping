/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_caps2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:19:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/03 23:59:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

void	tc_restore_cursor(void)
{
	char	*rc;

	rc = tgetstr("rc", NULL);
	if (rc)
		tputs(rc, 1, (int (*)(int))putchar);
	else
		ft_putstr_fd("\0338", STDOUT_FILENO);
}

/* bold/attribute toggles */
void	tc_enter_bold(void)
{
	char	*md;

	md = tgetstr("md", NULL);
	if (md)
		tputs(md, 1, (int (*)(int))putchar);
	else
		ft_putstr_fd("\033[1m", STDOUT_FILENO);
}

void	tc_exit_attr(void)
{
	char	*me;

	me = tgetstr("me", NULL);
	if (me)
		tputs(me, 1, (int (*)(int))putchar);
	else
		ft_putstr_fd("\033[0m", STDOUT_FILENO);
}
