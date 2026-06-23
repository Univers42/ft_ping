/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setlocale_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:54:41 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/25 19:56:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_setlocale.h"
#include "ft_string.h"
#include "ft_memory.h"

/* validate category index */
int	valid_category(int category)
{
	if (category < 0)
		return (0);
	if (category >= FT_CAT_COUNT)
		return (0);
	return (1);
}

/* initialize defaults for a newly allocated store */
void	init_store_defaults(t_loc *p)
{
	size_t	i;
	int		idx;

	ft_memset(p, 0, sizeof(*p));
	p->mb_cur_max = 4;
	idx = FT_LC_CTYPE;
	if (idx < 0 || idx >= FT_CAT_COUNT)
		idx = 0;
	ft_strncpy(p->locales[idx], "C", LOCSIZE - 1);
	p->locales[idx][LOCSIZE - 1] = '\0';
	(void)i;
}

/* ensure singleton exists */
t_loc	*ensure_store(void)
{
	t_loc	**pp;
	t_loc	*p;

	pp = loc_ptr();
	if (*pp)
		return (*pp);
	p = fn_malloc(sizeof(*p));
	if (!p)
		return (NULL);
	init_store_defaults(p);
	*pp = p;
	return (p);
}

/* pick environment locale or "C" fallback */
const char	*find_env_locale(void)
{
	const char	*env;

	env = getenv("LC_ALL");
	if (!env || !*env)
		env = getenv("LC_CTYPE");
	if (!env || !*env)
		env = getenv("LANG");
	if (!env || !*env)
		env = getenv("LC_COLLATE");
	if (!env)
		env = "C";
	return (env);
}

/* update mb_cur_max based on locale string */
void	update_mb_cur_max(t_loc *store, const char *str)
{
	if (ft_strstr(str, "UTF-8")
		|| ft_strstr(str, "utf8")
		|| ft_strstr(str, "UTF8"))
		store->mb_cur_max = 4;
	else
		store->mb_cur_max = 1;
}
