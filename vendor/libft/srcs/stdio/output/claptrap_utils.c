/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   claptrap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:20:33 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 15:34:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include <stdlib.h>

/* single shared state implementation */
t_clap_state	*get_clap_state(void)
{
	static t_clap_state	state = {NULL, 0, 0};

	return (&state);
}

/* choose prefix based on flag */
const char	*select_prefix(int flag)
{
	if (flag & CLAP_WARNING)
		return ("\033[33m ⚠️ [WARNING] ");
	if (flag & CLAP_ERROR)
		return ("\033[31m ❌ [ERROR] ");
	if (flag & CLAP_INFO)
		return ("\033[34m ℹ️ [INFO] ");
	if (flag & CLAP_SUCCESS)
		return ("\033[32m ✅ [SUCCESS] ");
	return ("\033[35m 🐤 [DEBUG] ");
}

/* build "<prefix><msg><suffix>" ; suf_len is constant 5 ("\033[0m\n") */
char	*build_formatted_msg(const char *prefix,
						const char *msg,
						size_t *out_len)
{
	size_t	pref_len;
	size_t	msg_len;
	size_t	suf_len;
	size_t	new_len;
	char	*res;

	pref_len = ft_strlen(prefix);
	msg_len = ft_strlen(msg);
	suf_len = ft_strlen("\033[0m\n");
	new_len = pref_len + msg_len + suf_len;
	res = fn_malloc(new_len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, prefix, pref_len);
	ft_memcpy(res + pref_len, msg, msg_len);
	ft_memcpy(res + pref_len + msg_len, "\033[0m\n", suf_len);
	res[new_len] = '\0';
	if (out_len)
		*out_len = new_len;
	return (res);
}

/* append formatted chunk to accumulator (realloc) */
int	append_accum(char *formatted, size_t new_len)
{
	char	*nacc;

	nacc = fn_realloc(get_clap_state()->accum,
			get_clap_state()->accum_len + new_len + 1);
	if (!nacc)
		return (0);
	get_clap_state()->accum = nacc;
	ft_memcpy(get_clap_state()->accum
		+ get_clap_state()->accum_len, formatted, new_len);
	get_clap_state()->accum_len += new_len;
	get_clap_state()->accum[get_clap_state()->accum_len] = '\0';
	return (1);
}

/* flush and free accumulator, reset state */
void	flush_accum(void)
{
	int	fd;

	if (!get_clap_state()->accum)
		return ;
	if (get_clap_state()->has_error)
		fd = STDERR_FILENO;
	else
		fd = STDOUT_FILENO;
	ft_fdputmem(fd,
		get_clap_state()->accum,
		(int)get_clap_state()->accum_len);
	fn_free(get_clap_state()->accum);
	get_clap_state()->accum = NULL;
	get_clap_state()->accum_len = 0;
	get_clap_state()->has_error = 0;
}
