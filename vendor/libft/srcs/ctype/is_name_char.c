/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 23:29:28 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/12 21:39:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

//[a-zA-Z_]
int	is_name_char(int c)
{
	return (ft_isalpha((unsigned char) c) || c == '_');
}

//[a-zA-Z0-9_]
int	is_int_name(int c)
{
	return (c == '_' || ft_isalnum((unsigned char)c));
}
