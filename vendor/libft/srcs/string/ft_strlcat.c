/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:31:28 by dyl-syzygy        #+#    #+#             */
/*   Updated: 2025/11/29 20:01:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "TDD/test.h"

t_size	ft_strlcat(char *dst, const char *src, t_size dsize)
{
	t_size	dest_len;
	t_size	src_len;
	t_size	i;
	char	*d;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dsize <= dest_len)
		return (dsize + src_len);
	d = dst + dest_len;
	i = -1;
	while (++i < dsize - dest_len - 1 && *src)
		*d++ = *src++;
	*d = '\0';
	return (dest_len + src_len);
}

//int main(void) {
//    char dst[] = "Hello, ";
//    char src[] = "World!";
//
//    // Test with a sufficient buffer size
//    size_t result = strlcat(dst, src, sizeof(dst));
//   	ft_printf("After ft_strlcat:\n");
//   	ft_printf("Destination: %s\n", dst);
//   	ft_printf("Total Length: %zu\n", result);
//
//    // Test with a smaller buffer size
//    char small_dst[10] = "Hello, ";
//    result = strlcat(small_dst, src, sizeof(small_dst));
//   	ft_printf("\nAfter ft_strlcat (small buffer):\n");
//   	ft_printf("Destination: %s\n", small_dst);
//   	ft_printf("Total Length: %zu\n", result);
//
//    return 0;
//}
