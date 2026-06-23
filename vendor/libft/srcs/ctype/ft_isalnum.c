/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:32:35 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/19 03:05:31 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
// #include "TDD/test.h"
/**
 * Checks if the given character is alphanumeric.
 * An alphanumeric character is either a digit (0-9) or a letter (A-Z, a-z).
 *
 * @param c The character to check (represented as an int)
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int	ft_isalnum(int c)
{
	unsigned int	is_digit;
	unsigned int	is_alpha;

	is_digit = ((unsigned)(c - '0') <= 9);
	is_alpha = ((unsigned)((c | 32) - 'a') < 26);
	return (is_digit || is_alpha);
}

// int ft_isspace(int c)
//{
//	return(c == ' ');
// }
// int is_valid_product_code(const char *code) {
//     int ft_strlen;
//
//     ft_strlen = ft_strlen(code);
//     if (code == NULL || ft_strlen < 2 || !ft_isalnum(*code))
//         return 0;
//     for (int i = 0; i < ft_strlen - 1; i++) {
//         if (!ft_isalnum(code[i]))
//             return 0;
//     }
//     if (ft_isspace(code[strlen - 4])
//         && !ft_isdigit(code[strlen - 3])
//         && !ft_isalnum(code[strlen - 2])
//         && ft_isalnum(code[strlen - 1]))
//         return 0;
//     return 1;
// }
//
// int main(void) {
//     char product_code[100];
//
//    	ft_printf("Enter the product code [i.e. f2133as1121fd5v1fdd54fd1]: ");
//     fgets(product_code, sizeof(product_code), stdin);
//
//     product_code[strcspn(product_code, "\n")] = 0;
//
//     if (is_valid_product_code(product_code))
//        	ft_printf("The product code '%s' is valid!\n", product_code);
//     else
//        	ft_printf("The product code '%s' is invalid.\n", product_code);
//
//     return 0;
// }
