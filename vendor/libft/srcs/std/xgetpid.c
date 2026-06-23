/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xgetpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:12:17 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/25 20:48:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ds.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "ft_stddef.h"
#include <unistd.h>
#include <fcntl.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		fn_free(tab[i++]);
	fn_free(tab);
}

#ifndef POSIXLY_CORRECT

char	*xgetpid(void)
{
	int			fd;
	t_vec		file;
	char		*ret;
	char		**temp;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
	{
		ft_eprintf("Error: Cannot open /proc/self/stat\n");
		return (0);
	}
	vec_init(&file);
	vec_append_fd(fd, &file);
	close(fd);
	temp = ft_split((char *)file.ctx, SPACE_CHAR);
	ret = ft_strdup(temp[0]);
	free_tab(temp);
	vec_destroy(&file, NULL);
	return (ret);
}

#else

char	*xgetpid(void)
{
	pid_t	pid;
	char	*ret;

	pid = getpid();
	ret = ft_itoa((int)pid);
	return (ret);
}

#endif