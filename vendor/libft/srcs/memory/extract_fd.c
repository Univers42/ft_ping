/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:23:57 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 23:10:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_memory.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define EXTRACT_CHUNK 4096
#define READ 0
#define CAP 1
#define LEN 2

char	*extract_fd(int fd)
{
	char	buf[EXTRACT_CHUNK];
	char	*acc;
	ssize_t	dyn_slot[3];

	dyn_slot[CAP] = EXTRACT_CHUNK;
	dyn_slot[LEN] = 0;
	acc = (char *)fn_malloc(dyn_slot[CAP]);
	if (!acc)
		return (NULL);
	dyn_slot[READ] = read(fd, buf, sizeof(buf));
	while (dyn_slot[READ] > 0)
	{
		if (dyn_slot[LEN] + (size_t)dyn_slot[READ] + 1 > (size_t)dyn_slot[CAP])
		{
			dyn_slot[CAP] = (dyn_slot[CAP] + dyn_slot[READ] + EXTRACT_CHUNK);
			acc = (char *)fn_realloc(acc, dyn_slot[CAP]);
			if (!acc)
				return (NULL);
		}
		ft_memcpy(acc + dyn_slot[LEN], buf, (size_t)dyn_slot[READ]);
		dyn_slot[LEN] += (size_t)dyn_slot[READ];
		dyn_slot[READ] = read(fd, buf, sizeof(buf));
	}
	acc[dyn_slot[LEN]] = '\0';
	return (acc);
}

int	capture_output(const char *cmd, char *buf, size_t cap)
{
	int		pp[2];
	pid_t	pid;
	ssize_t	n;
	size_t	off;

	off = 0;
	if (cap == 0 || pipe(pp) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		((dup2(pp[1], STDOUT_FILENO), close(pp[0]), close(pp[1])),
			(execl("/bin/sh", "sh", "-c", cmd, (char *)0), _exit(127)));
	close(pp[1]);
	n = read(pp[0], buf + off, cap - 1 - off);
	while (n > 0)
		off += (size_t)n;
	if (off < cap)
		buf[off] = '\0';
	else if (cap > 0)
		buf[cap - 1] = '\0';
	close(pp[0]);
	while (waitpid(pid, NULL, 0) == -1 && errno == EINTR)
		;
	return (0);
}
