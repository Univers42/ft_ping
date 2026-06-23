/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:32:19 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:11:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H
# include <stdlib.h>
# include "ft_memory.h"
# include <stdbool.h>
# include "../srcs/std/strto/strto.h"
# include "../srcs/std/prng.h"

# include <stddef.h>

# ifndef RAND_MAX
#  define RAND_MAX 32767
# endif

typedef enum e_rng_type
{
	RNG_LCG = 0,
	RNG_XORSHIFT,
	RNG_MIDDLE_SQUARE,
	RNG_MAX_TYPES
}	t_rng_type;

typedef struct s_rng_state
{
	unsigned long	seed_lcg;
	unsigned long	seed_xorshift;
	unsigned long	seed_middle;
	t_rng_type		current_type;
}	t_rng_state;

char			*ft_itoa(int n);
char			*ft_utoa(unsigned int n);
char			*ft_xtoa(unsigned long int num, int is_upper);
int				ft_atoi(const char *nptr);
void			ft_putnbr_base(int nbr, char *radix);
int				ft_atoi_base(const char *str, int base);
void			*ft_calloc(t_size nmemb, t_size size);
// Remove or comment out this line if you want to use your custom fn_realloc3
// void	*fn_realloc3(void *ptr, t_size old, t_size new);
void			skip_spaces(int *i, int size, char *str);
void			dbl_free(char **ptr);
void			*fn_realloc3(void *ptr, size_t old_cap, size_t new_cap);
// RAND section
void			ft_srand(unsigned int new_seed, int select);
int				ft_rand(void);
t_rng_state		*get_rng_state(void);
const char		*get_algorithm_name(int type);
size_t			ft_offsetof(void *struct_base, void *member_addr);
char			*xgetpid(void);
int				write_file(const char *str, int fd);
void			free_tab(char **tab);

#endif
