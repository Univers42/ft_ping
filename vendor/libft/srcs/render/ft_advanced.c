/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/12/20 03:29:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"
#include "ft_colors.h"
#include "ft_stdio.h"
#include "ft_string.h"

void	ft_print_notification(const char *title, const char *message,
			const char *type)
{
	const char	*color;

	if (!title || !message || !type)
		return ;
	color = ASCII_GREEN;
	if (ft_strcmp(type, "error") == 0)
		color = ASCII_RED;
	else if (ft_strcmp(type, "warning") == 0)
		color = ASCII_YELLOW;
	ft_printf("%s[%s] %s: %s%s\n", color, type, title, message, RESET_TERM);
}

void	ft_print_code_block(const char *code, const char *language)
{
	const char	*lang_name;

	if (!code)
		return ;
	lang_name = "Code";
	if (language)
		lang_name = language;
	ft_printf("%s--- %s ---%s\n", ASCII_BLUE, lang_name, RESET_TERM);
	ft_printf("%s%s%s\n", DIM_TERM, code, RESET_TERM);
	ft_printf("%s----------%s\n", ASCII_BLUE, RESET_TERM);
}

void	ft_print_diff(const char *old_line, const char *new_line)
{
	if (!old_line || !new_line)
		return ;
	ft_printf("%s- %s%s\n", ASCII_RED, old_line, RESET_TERM);
	ft_printf("%s+ %s%s\n", ASCII_GREEN, new_line, RESET_TERM);
}

void	ft_print_emoji_status(const char *message, const char *emoji)
{
	if (!message || !emoji)
		return ;
	ft_printf("%s %s%s %s%s\n", emoji, ASCII_GREEN, message, RESET_TERM, emoji);
}
