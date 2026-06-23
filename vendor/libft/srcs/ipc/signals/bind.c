/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:49:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/05 21:14:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

void	unbind_variable_noref(const char *name)
{
	(void)name;
}

void	bind_variable(const char *name, const char *value, int flags)
{
	(void)name;
	(void)value;
	(void)flags;
}

void	bind_var_to_int(const char *name, int value, int flags)
{
	(void)name;
	(void)value;
	(void)flags;
}

char	*get_string_value(const char *name)
{
	(void)name;
	return (NULL);
}
