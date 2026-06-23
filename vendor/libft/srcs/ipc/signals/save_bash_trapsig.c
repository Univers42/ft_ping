/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bash_trapsig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:47:11 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/05 02:14:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trap.h"

char	*save_bash_trapsig(void)
{
	char	*ret;

	ret = get_string_value("BASH_TRAPSIG");
	if (ret)
		ret = savestring(ret);
	return (ret);
}
