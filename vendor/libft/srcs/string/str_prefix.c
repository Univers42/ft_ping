/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:08:00 by alcacere          #+#    #+#             */
/*   Updated: 2025/12/01 14:18:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*prefix(const char *string, const char *pfx)
{
	while (*pfx)
		if (*pfx++ != *string++)
			return (0);
	return ((char *) string);
}
