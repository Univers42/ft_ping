/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:15:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/11/30 00:39:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef struct s_q_ctx
{
	char	*p;
	char	*q;
	size_t	len;
}	t_sq_ctx;

#endif
