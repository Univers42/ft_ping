/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setlocale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:50:35 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 15:50:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_setlocale.h"
#include "ft_string.h"
#include "ft_memory.h"

/* set locale from environment into given category */
static char	*set_locale_from_env(t_loc *store, int category)
{
	const char	*env;

	env = find_env_locale();
	ft_strncpy(store->locales[category], env, LOCSIZE - 1);
	store->locales[category][LOCSIZE - 1] = '\0';
	update_mb_cur_max(store, env);
	return (store->locales[category]);
}

/* copy provided locale string into store and update width */
static char	*store_locale(t_loc *store,
						int category,
						const char *locale)
{
	ft_strncpy(store->locales[category], locale, LOCSIZE - 1);
	store->locales[category][LOCSIZE - 1] = '\0';
	update_mb_cur_max(store, locale);
	return (store->locales[category]);
}

char	*ft_setlocale(int category, const char *locale)
{
	t_loc	*store;

	store = ensure_store();
	if (!store)
		return (NULL);
	if (!valid_category(category))
		return (NULL);
	if (locale == NULL)
	{
		if (store->locales[category][0])
			return (store->locales[category]);
		return (NULL);
	}
	if (locale[0] == '\0')
		return (set_locale_from_env(store, category));
	return (store_locale(store, category, locale));
}

size_t	ft_mb_cur_max(void)
{
	t_loc	*store;

	store = ensure_store();
	if (!store)
		return (4);
	return (store->mb_cur_max);
}

void	ft_locale_cleanup(void)
{
	t_loc	**pp;

	pp = loc_ptr();
	if (!pp || !*pp)
		return ;
	fn_free(*pp);
	*pp = NULL;
}

/* ************************************************************************** */
/*                              TEST MAIN                                     */
/* ************************************************************************** */

// #include <stdio.h>
//
// int	main(void)
//{
//	char	*loc;
//
//	printf("=== ft_setlocale Test (Norminette Compliant) ===\n\n");
//	loc = ft_setlocale(FT_LC_ALL, NULL);
//	printf("Current locale: %s\n", loc ? loc : "(null)");
//	loc = ft_setlocale(FT_LC_ALL, "C");
//	printf("After setting to 'C': %s\n", loc ? loc : "(null)");
//	loc = ft_setlocale(FT_LC_ALL, "en_US.UTF-8");
//	printf("After setting to 'en_US.UTF-8': %s\n", loc ? loc : "(null)");
//	loc = ft_setlocale(FT_LC_ALL, "");
//	printf("After setting to environment: %s\n", loc ? loc : "(null)");
//	loc = ft_setlocale(FT_LC_NUMERIC, "fr_FR.UTF-8");
//	printf("FT_LC_NUMERIC set to: %s\n", loc ? loc : "(null)");
//	loc = ft_setlocale(FT_LC_NUMERIC, NULL);
//	printf("Current FT_LC_NUMERIC: %s\n", loc ? loc : "(null)");
//	loc = ft_setlocale(999, "C");
//	printf("Invalid category result: %s\n", loc ? loc : "(null)");
//	ft_locale_cleanup();
//	return (0);
// }
