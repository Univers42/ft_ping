# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    global_conf.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 19:30:00 by dlesieur          #+#    #+#              #
#    Updated: 2025/12/11 15:52:22 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════
# ║                            COLOR DEFINITIONS                             ║
# ════════════════════════════════════════════════════════════════════════════

# Use a real escape character so printf will emit colors instead of the literal "\033"
ESC := $(shell printf '\033')

ESC_BLACK = $(ESC)[0;30m
ESC_RED = $(ESC)[0;31m
ESC_GREEN = $(ESC)[0;32m
ESC_YELLOW = $(ESC)[0;33m
ESC_BLUE = $(ESC)[0;34m
ESC_MAGENTA = $(ESC)[0;35m
ESC_CYAN = $(ESC)[0;36m
ESC_WHITE = $(ESC)[0;37m

## Bold colors
ESC_BOLD_BLACK = $(ESC)[1;30m
ESC_BOLD_RED = $(ESC)[1;31m
ESC_BOLD_GREEN = $(ESC)[1;32m
ESC_BOLD_YELLOW = $(ESC)[1;33m
ESC_BOLD_BLUE = $(ESC)[1;34m
ESC_BOLD_MAGENTA = $(ESC)[1;35m
ESC_BOLD_CYAN = $(ESC)[1;36m
ESC_BOLD_WHITE = $(ESC)[1;37m
#
## Background colors
ESC_BG_BLACK = $(ESC)[40m
ESC_BG_RED = $(ESC)[41m
ESC_BG_GREEN = $(ESC)[42m
ESC_BG_YELLOW = $(ESC)[43m
ESC_BG_BLUE = $(ESC)[44m
ESC_BG_MAGENTA = $(ESC)[45m
ESC_BG_CYAN = $(ESC)[46m
ESC_BG_WHITE = $(ESC)[47m
#
## Special formatting
ESC_RESET = $(ESC)[0m
ESC_BOLD = $(ESC)[1m
ESC_DIM = $(ESC)[2m
ESC_ITALIC = $(ESC)[3m
ESC_UNDERLINE = $(ESC)[4m
ESC_BLINK = $(ESC)[5m
ESC_REVERSE = $(ESC)[7m
ESC_STRIKETHROUGH = $(ESC)[9m
#
## Enhanced colors and formatting
ESC_BRIGHT_GREEN = $(ESC)[1;32m
ESC_BRIGHT_RED = $(ESC)[1;31m
ESC_BRIGHT_YELLOW = $(ESC)[1;33m
ESC_BRIGHT_BLUE = $(ESC)[1;34m
ESC_BRIGHT_MAGENTA = $(ESC)[1;35m
ESC_BRIGHT_CYAN = $(ESC)[1;36m

## Faded bold gray (bold + dim + white)
#FADED_BOLD_GRAY = $(ESC)[1;2;37m

BLACK        := $(shell printf '\033[0;30m')
RED          := $(shell printf '\033[0;31m')
GREEN        := $(shell printf '\033[0;32m')
YELLOW       := $(shell printf '\033[0;33m')
BLUE         := $(shell printf '\033[0;34m')
MAGENTA      := $(shell printf '\033[0;35m')
CYAN         := $(shell printf '\033[0;36m')
WHITE        := $(shell printf '\033[0;37m')

# Bold colors
BOLD_BLACK   := $(shell printf '\033[1;30m')
BOLD_RED     := $(shell printf '\033[1;31m')
BOLD_GREEN   := $(shell printf '\033[1;32m')
BOLD_YELLOW  := $(shell printf '\033[1;33m')
BOLD_BLUE    := $(shell printf '\033[1;34m')
BOLD_MAGENTA := $(shell printf '\033[1;35m')
BOLD_CYAN    := $(shell printf '\033[1;36m')
BOLD_WHITE   := $(shell printf '\033[1;37m')

# Background colors
BG_BLACK     := $(shell printf '\033[40m')
BG_RED       := $(shell printf '\033[41m')
BG_GREEN     := $(shell printf '\033[42m')
BG_YELLOW    := $(shell printf '\033[43m')
BG_BLUE      := $(shell printf '\033[44m')
BG_MAGENTA   := $(shell printf '\033[45m')
BG_CYAN      := $(shell printf '\033[46m')
BG_WHITE     := $(shell printf '\033[47m')

# Special formatting
RESET        := $(shell printf '\033[0m')
BOLD         := $(shell printf '\033[1m')
DIM          := $(shell printf '\033[2m')
ITALIC       := $(shell printf '\033[3m')
UNDERLINE    := $(shell printf '\033[4m')
BLINK        := $(shell printf '\033[5m')
REVERSE      := $(shell printf '\033[7m')
STRIKETHROUGH:= $(shell printf '\033[9m')

# Enhanced colors and formatting
BRIGHT_GREEN := $(shell printf '\033[1;32m')
BRIGHT_RED   := $(shell printf '\033[1;31m')
BRIGHT_YELLOW:= $(shell printf '\033[1;33m')
BRIGHT_BLUE  := $(shell printf '\033[1;34m')
BRIGHT_MAGENTA:= $(shell printf '\033[1;35m')
BRIGHT_CYAN  := $(shell printf '\033[1;36m')

# State-specific colors (used by logging macro)
STATE_COLOR_INFO  := $(BRIGHT_CYAN)
STATE_COLOR_WARN  := $(BRIGHT_YELLOW)
STATE_COLOR_OK    := $(BRIGHT_GREEN)
STATE_COLOR_NOTE  := $(BRIGHT_MAGENTA)
STATE_COLOR_ERROR := $(BRIGHT_RED)
STATE_COLOR_DEBUG := $(BRIGHT_BLUE)

CC				:= cc
CXX				:= CXX
CSTD			?= -std=gnu99
CXXSTD			?= -std=gnu++17
DEFINES			?= -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L
PREPROCFLAGS	?= -MMD -MP -MF
DPDCS_STATIC	?= $(sh -c "git submodule foreach --quiet 'echo $paht'")
DPDCS_SLIB		?= 
SUBMODULE_URLS	?= git@github.com:Univers42/libft.git
SUBMODULE_DIRS	?= 
WARN_FLAGS		?=	-Wall -Wextra -Werror -pedantic \
					-Wshadow -Wpointer-arith -Wcast-align -Wvolatile-register-var \
					-Wdangling-else -Wenum-compare -Wexpansion-to-defined -Waddress \
					-Wno-shift-count-overflow -Wstrict-overflow -Wfatal-errors

CXXFLAGS		?= $(CXXSTD) -fpermissive $(WARN_FLAGS) $(DEBFLAGS) $(CPPFLAGS)
ANAFLAGS		?= -fsanitize=address,undefined,leak
CFLAGS			?= $(CSTD) $(WARN_FLAGS) $(DEBFLAGS) $(ANAFLAGS) $(DEFINES)
DEBFLAGS		?= -g3 -O0 -ggdb
OPTFLAGS		?= -Ofast -pipe
SOURCES_DIR		?= srcs
OBJ_DIR			:= obj
LDFLAGS			:= $(DPDCS_STATIC) 
RM				:= rm -rf
AR				:= ar rcs