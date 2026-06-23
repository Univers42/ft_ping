/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:34:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:02:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dcopy;

	if (!dest || !src)
		return (NULL);
	dcopy = dest;
	while (*src)
		*dest++ = *src++;
	*dest++ = '\0';
	return (dcopy);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (dest);
	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

//#include "TDD/test.h"
/**
 * Copies up to `dsize - 1` characters from the 
 * string `src` to `dst`, ensuring that the
 * destination buffer is null-terminated. 
 * If `dsize` is less than or equal to the length of `src`,
 * the string will be truncated.
 * 
 * @param dst The destination buffer where the string will be copied.
 * @param src The source string to copy from.
 * @param dsize The size of the destination buffer `dst`.
 * @return The length of the source string `src`.
 * 
 * @note 
 * The function copies at most `dsize - 1` characters 
 * from `src` to `dst`, ensuring that the      
 * resulting string in `dst` is null-terminated. 
 * If `dsize` is greater than the length of `src`,
 * the function copies the entire string and adds
 *  a null terminator. If `dsize` is smaller than
 * or equal to the length of `src`, the string is
 *  truncated and the null terminator is not added.
 */
t_size	ft_strlcpy(char *dst, const char *src, t_size dsize)
{
	t_size	i;

	i = 0;
	if (dsize > 0)
	{
		while (src[i] != '\0' && i < dsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*strpcpy(char *dst, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	dst[len] = 0;
	return (ft_memcpy(dst, src, len));
}
