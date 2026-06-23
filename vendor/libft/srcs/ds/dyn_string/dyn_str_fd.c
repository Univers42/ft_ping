/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:48:58 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/27 16:16:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ds.h"
#include "ft_stdio.h"

// void	str_append_fd(int fd)
// {
// 	char	buff[1024];
// 	int		len;

// 	while (ST_SCANNING)
// 	{
// 		len = read(fd, buff, sizeof(buff));
// 		if (len == 0)
// 			break ;
// 		if (len > 0)
// 			str_pushnstr(buff, len);
// 		else
// 			critical_error_errno_ctx("read");
// 	}
// }

// void	dyn_str_append_fd(t_dyn_str *str, int fd)
// {
// 	char	buff[24];
// 	int		len;

// 	while (ST_SCANNING)
// 	{
// 		len = read(fd, buff, sizeof(buff));
// 		if (len == 0)
// 			break ;
// 		if (len > 0)
// 			dyn_str_pushnstr(str, buff, len);
// 		else
// 			critical_error_errno_ctx("read");
// 	}
// }
