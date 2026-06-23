/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_codepoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:44:41 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/23 15:47:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>

/**
 * Converts a UTF-8 multibyte sequence into a single `wchar_t`
 * WE need to detect UTF-8 sequence length from the first byte
 * |Leading byte        |Sequence length|
 * |0xxxxxxx            |1 byte         |
 * |110xxxxx            |2 bytes		|
 * |1110xxxx			|3 bytes		|
 * |11110xxx			|4 bytes		|
 * 
 * Then we need to validate continuation bytes (10xxxxxx)
 * Aseembe codepoints:
 * 
 * @note:
 * does not fully support stateful encodings (like shift-JIS,, EUC-JP)
 * only for UTF-8;
 */

wchar_t	asm_codepoint(size_t needed, const unsigned char *s)
{
	wchar_t		wc;

	wc = 0;
	if (needed == 2)
		wc = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
	else if (needed == 3)
		wc = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
	else if (needed == 4)
		wc = ((s[0] & 0x07) << 18)
			| ((s[1] & 0x3F) << 12)
			| ((s[2] & 0x3F) << 6)
			| (s[3] & 0x3F);
	return (wc);
}
