/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:48:37 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 22:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

// char *
// array_to_assign (t_arr *a, int quoted)
// {
// 	char	*result, *valstr, *is;
// 	char	indstr[INT_STRLEN_BOUND(intmax_t) + 1];
// 	ARRAY_ELEMENT *ae;
// 	int	rsize, rlen, elen;

// 	if (a == 0 || array_empty (a))
// 		return((char *)NULL);

// 	result = (char *)malloc (rsize = 128);
// 	result[0] = '(';
// 	rlen = 1;

// 	for (ae = element_forw(a->head); ae != a->head; ae = element_forw(ae)) {
// 		is = inttostr (element_index(ae), indstr, sizeof(indstr));
// 		valstr = element_value (ae) ?
// 				(ansic_shouldquote (element_value (ae)) ?
// 				   ansic_quote (element_value(ae), 0, (int *)0) :
// 				   sh_double_quote (element_value (ae)))
// 					    : (char *)NULL;
// 		elen = ft_strlen (is) + 8 + ft_strlen (valstr);
// 		RESIZE_MALLOCED_BUFFER (result, rlen, (elen + 1), rsize, rsize);

// 		result[rlen++] = '[';
// 		strcpy (result + rlen, is);
// 		rlen += ft_strlen (is);
// 		result[rlen++] = ']';
// 		result[rlen++] = '=';
// 		if (valstr) {
// 			strcpy (result + rlen, valstr);
// 			rlen += ft_strlen (valstr);
// 		}

// 		if (element_forw(ae) != a->head)
// 		  result[rlen++] = ' ';

// 		FREE (valstr);
// 	}
// 	RESIZE_MALLOCED_BUFFER (result, rlen, 1, rsize, 8);
// 	result[rlen++] = ')';
// 	result[rlen] = '\0';
// 	if (quoted) {
// 		/* This is not as efficient as it could be... */
// 		valstr = sh_single_quote (result);
// 		free (result);
// 		result = valstr;
// 	}
// 	return(result);
// }
