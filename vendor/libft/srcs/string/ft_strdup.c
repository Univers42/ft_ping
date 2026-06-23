/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:02:28 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/11/30 00:54:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

//#include "TDD/test.h"
/**
 * Creates a new string by duplicating the string `s`.
 * 
 * @param s The string to duplicate.
 * @return 
 * A pointer to the newly allocated string, 
 * or NULL if memory allocation fails.
 * 
 * @note 
 * The function allocates memory for a new string 
 * and copies the contents of `s` into it.
 * The newly allocated string is null-terminated.
 */
char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*cpy;

	dup = fn_malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	cpy = dup;
	while (*s)
		*dup++ = *s++;
	*dup = '\0';
	return (cpy);
}

char	*ft_sstrdup(const char *p)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(p) + 1;
	dst = fn_malloc(len);
	if (!dst)
		return (NULL);
	return (ft_memcpy(dst, p, len));
}
//int main(void)
//{
//	char *str = ft_strdup("hello, world!");
//	if(!str)
//		return 1;
//	ft_printf("%s", str);
//	free(str);
//	return (0);
//}
