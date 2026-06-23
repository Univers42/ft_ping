/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:10:27 by dlesieur          #+#    #+#             */
/*   Updated: 2026/01/24 01:02:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H

// Reset
# define RESET_TERM						"\033[0m"
# define ASCII_RESET					"\033[0m"

// Regular colors
# define ASCII_BLACK					"\033[0;30m"
# define ASCII_GREY     				"\033[0;37m"
# define ASCII_RED						"\033[0;31m"
# define ASCII_GREEN					"\033[0;32m"
# define ASCII_YELLOW					"\033[0;33m"
# define ASCII_BLUE						"\033[0;34m"
# define ASCII_MAGENTA					"\033[0;35m"
# define ASCII_CYAN						"\033[0;36m"
# define ASCII_WHITE					"\033[0;37m"
# define ASCII_BOLD						"\033[1m"

// Bright colors
# define BRIGHT_BLACK_TERM				"\033[1;30m"
# define BRIGHT_RED_TERM				"\033[1;31m"
# define BRIGHT_GREEN_TERM				"\033[1;32m"
# define BRIGHT_ASCII_YELLOW			"\033[1;33m"
# define BRIGHT_BLUE_TERM				"\033[1;34m"
# define BRIGHT_MAGENTA_TERM			"\033[1;35m"
# define BRIGHT_CYAN_TERM				"\033[1;36m"
# define BRIGHT_WHITE_TERM				"\033[1;37m"

// Dim and bold
# define DIM_TERM						"\033[2m"
# define BOLD_TERM      				"\033[1m"

# define FG_FIRE							"\001\033[38;5;196m\002"
# define FG_MOLTEN						"\001\033[38;5;208m\002"
# define FG_EMBER						"\001\033[38;5;214m\002"
# define FG_LAVA							"\001\033[38;5;202m\002"
# define FG_ASH							"\001\033[38;5;245m\002"
# define FG_CHARCOAL						"\001\033[38;5;240m\002"
# define FG_DIM							"\001\033[38;5;238m\002"
# define FG_SUCCESS						"\001\033[38;5;82m\002"
# define FG_WARN							"\001\033[38;5;220m\002"
# define FG_BLOOD						"\001\033[38;5;124m\002"
# define FG_CYAN							"\001\033[38;5;87m\002"
# define FG_MAGENTA						"\001\033[38;5;213m\002"
# define FG_PURPLE						"\001\033[38;5;135m\002"
# define FG_BLUE							"\001\033[38;5;27m\002"
# define BOLD							"\001\033[1m\002"
# define RESET							"\001\033[0m\002"

# define SEP_L							" ═══ "
# define SEP_R							" ═══ "
# define SEP_GIT							" ║ "
# define SEP_THIN						" ─── "
# define GIT_ICON						""
# define DIRTY							"●"
# define CLEAN							"○"
# define TIMER_ICON						"⏱"
# define ARROW_OK						" ●"
# define ARROW_FAIL						"✗"
# define ARROW_WARN						"⚠"
# define USER_ICON						""
# define DIR_ICON						""

#endif
