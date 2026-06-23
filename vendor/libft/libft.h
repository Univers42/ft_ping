/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:22:22 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 15:36:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* Feature test macros - define before any system includes */
# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# ifndef _BSD_SOURCE
#  define _BSD_SOURCE
# endif

// # include "analyzer.h"
# include "./include/xalloc.h"
# include "./include/ds.h"
# include "./include/ft_colors.h"
# include "./include/ft_ctype.h"
# include "./include/ft_debug.h"
# include "./include/ft_math.h"
# include "./include/ft_memory.h"
# include "./include/ft_render.h"
# include "./include/ft_sort.h"
# include "./include/ft_stddef.h"
# include "./include/ft_stdio.h"
# include "./include/ft_stdlib.h"
# include "./include/ft_string.h"
# include "./include/ft_termcap.h"
# include "./include/ft_time.h"
# include "./include/ft_wctype.h"
# include "./include/ipc.h"
# include "./include/system.h"

# include <immintrin.h>
# include <unistd.h>
# include <signal.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>

#endif
