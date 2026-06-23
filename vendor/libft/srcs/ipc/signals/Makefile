# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/08 06:45:29 by dlesieur          #+#    #+#              #
#    Updated: 2025/11/28 02:22:16 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              := cc
CFLAGS          := -Wall -Wextra -Werror -Wshadow -I.
DEPFLAGS        := -MMD -MP

# C++ compiler for program/demo binaries
CXX            := g++
CXXFLAGS       := -Wall -Wextra -Werror -I.
# If you need a specific standard, uncomment:
# CXXFLAGS       += -std=c++17

# --- Pretty color output ---
COLOR_RESET := \033[0m
COLOR_CC    := \033[1;34m   # bold blue
COLOR_LD    := \033[1;32m   # bold green
COLOR_AR    := \033[1;35m   # bold magenta
COLOR_INFO  := \033[1;33m   # bold yellow

VERBOSE ?= 0
# If you want raw verbose commands, run: make VERBOSE=1

NAME_LIB        := libsig
LIB_FILE        := $(NAME_LIB).a

OBJ_DIR         := obj
BIN_DIR         := bin
PROGRAMS_DIR    := programs

# Root sources (library) = all .c and .bak in this directory (exclude programs/)
# We turn filenames into base-names and build obj/<base>.o so .bak is treated like .c.
SRCS_LIB        := $(wildcard *.c) $(wildcard *.bak)
SRCS_BASENAME   := $(basename $(notdir $(SRCS_LIB)))
OBJ_LIB         := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(SRCS_BASENAME)))
DEP_LIB         := $(OBJ_LIB:.o=.d)

# Programs (each has one source for now)
PROG_SRC_demo_main      := $(PROGRAMS_DIR)/demo_main.cpp
PROG_SRC_demo_posix     := $(PROGRAMS_DIR)/posix_example.cpp
PROG_SRC_demo_sigaction := $(PROGRAMS_DIR)/demo_sigaction.cpp
PROG_SRC_demo_kill      := $(PROGRAMS_DIR)/demo_kill.cpp
PROG_SRC_demo_leak      := $(PROGRAMS_DIR)/demo_leak.cpp
PROG_SRC_demo_zombie    := $(PROGRAMS_DIR)/demo_zombie.cpp
PROG_SRC_demo_shell     := $(PROGRAMS_DIR)/demo_shell.cpp
PROG_SRC_demo_signals   := $(PROGRAMS_DIR)/demo_signals.cpp

PROG_OBJ_demo_main      := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_main.o
PROG_OBJ_demo_posix     := $(OBJ_DIR)/$(PROGRAMS_DIR)/posix_example.o
PROG_OBJ_demo_sigaction := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_sigaction.o
PROG_OBJ_demo_kill      := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_kill.o
PROG_OBJ_demo_leak      := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_leak.o
PROG_OBJ_demo_zombie    := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_zombie.o
PROG_OBJ_demo_shell     := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_shell.o
PROG_OBJ_demo_signals   := $(OBJ_DIR)/$(PROGRAMS_DIR)/demo_signals.o

PROG_BIN_demo_main      := $(BIN_DIR)/demo_main
PROG_BIN_demo_posix     := $(BIN_DIR)/demo_posix
PROG_BIN_demo_sigaction := $(BIN_DIR)/demo_sigaction
PROG_BIN_demo_kill      := $(BIN_DIR)/demo_kill
PROG_BIN_demo_leak      := $(BIN_DIR)/demo_leak
PROG_BIN_demo_zombie    := $(BIN_DIR)/demo_zombie
PROG_BIN_demo_shell     := $(BIN_DIR)/demo_shell
PROG_BIN_demo_signals   := $(BIN_DIR)/demo_signals

PROGRAM_BINS := \
	$(PROG_BIN_demo_main) \
	$(PROG_BIN_demo_posix) \
	$(PROG_BIN_demo_sigaction) \
	$(PROG_BIN_demo_kill) \
	$(PROG_BIN_demo_leak) \
	$(PROG_BIN_demo_zombie) \
	$(PROG_BIN_demo_shell) \
	$(PROG_BIN_demo_signals)

# Readline libs for shell demo
READLINE_LIBS := -lreadline -lncurses

# Default
all: $(LIB_FILE)

# Test target (build demo programs on demand)
test: demo
	@echo "Built test -> demo programs are in $(BIN_DIR)"

# Archive
$(LIB_FILE): $(OBJ_LIB)
ifeq ($(VERBOSE),1)
	@echo "[AR] $@"
	@ar rcs $@ $(OBJ_LIB)
else
	@printf "%b\n" "$(COLOR_AR)[AR] $@$(COLOR_RESET)"
	@ar rcs $@ $(OBJ_LIB)
endif

# Root objects
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
ifeq ($(VERBOSE),1)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
else
	@printf "%b\n" "$(COLOR_CC)[CC] $< -> $@$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
endif

# Also accept .bak files as C sources (force C language)
$(OBJ_DIR)/%.o: %.bak | $(OBJ_DIR)
	@mkdir -p $(dir $@)
ifeq ($(VERBOSE),1)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -x c -c $< -o $@
else
	@printf "%b\n" "$(COLOR_CC)[CC] $< -> $@$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -x c -c $< -o $@
endif

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Program objects
$(OBJ_DIR)/$(PROGRAMS_DIR)/%.o: $(PROGRAMS_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) -I. -c $< -o $@
else
	@printf "%b\n" "$(COLOR_CC)[CXX] $< -> $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) -I. -c $< -o $@
endif

# Link programs
$(PROG_BIN_demo_main): $(LIB_FILE) $(PROG_OBJ_demo_main) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_main) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_main) $(LIB_FILE) -o $@
endif

$(PROG_BIN_demo_posix): $(LIB_FILE) $(PROG_OBJ_demo_posix) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_posix) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_posix) $(LIB_FILE) -o $@
endif

$(PROG_BIN_demo_sigaction): $(LIB_FILE) $(PROG_OBJ_demo_sigaction) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_sigaction) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_sigaction) $(LIB_FILE) -o $@
endif

$(PROG_BIN_demo_kill): $(LIB_FILE) $(PROG_OBJ_demo_kill) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_kill) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_kill) $(LIB_FILE) -o $@
endif

$(PROG_BIN_demo_leak): $(LIB_FILE) $(PROG_OBJ_demo_leak) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_leak) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_leak) $(LIB_FILE) -o $@
endif

$(PROG_BIN_demo_zombie): $(LIB_FILE) $(PROG_OBJ_demo_zombie) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_zombie) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_zombie) $(LIB_FILE) -o $@
endif

$(PROG_BIN_demo_shell): $(LIB_FILE) $(PROG_OBJ_demo_shell) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_shell) $(LIB_FILE) $(READLINE_LIBS) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_shell) $(LIB_FILE) $(READLINE_LIBS) -o $@
endif

$(PROG_BIN_demo_signals): $(LIB_FILE) $(PROG_OBJ_demo_signals) | $(BIN_DIR)
ifeq ($(VERBOSE),1)
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_signals) $(LIB_FILE) -o $@
else
	@printf "%b\n" "$(COLOR_LD)[LD] $@$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -I. $(PROG_OBJ_demo_signals) $(LIB_FILE) -o $@
endif

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Public demo targets
demo_main: $(PROG_BIN_demo_main)
	@echo "Built $@ -> $(PROG_BIN_demo_main)"

demo_posix: $(PROG_BIN_demo_posix)
	@echo "Built $@ -> $(PROG_BIN_demo_posix)"

demo_sigaction: $(PROG_BIN_demo_sigaction)
	@echo "Built $@ -> $(PROG_BIN_demo_sigaction)"

demo_kill: $(PROG_BIN_demo_kill)
	@echo "Built $@ -> $(PROG_BIN_demo_kill)"

demo_leak: $(PROG_BIN_demo_leak)
	@echo "Built $@ -> $(PROG_BIN_demo_leak)"

demo_zombie: $(PROG_BIN_demo_zombie)
	@echo "Built $@ -> $(PROG_BIN_demo_zombie)"

demo_shell: $(PROG_BIN_demo_shell)
	@echo "Built $@ -> $(PROG_BIN_demo_shell)"

demo_signals: $(PROG_BIN_demo_signals)
	@echo "Built $@ -> $(PROG_BIN_demo_signals)"

demo: $(PROGRAM_BINS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(LIB_FILE) $(BIN_DIR) test_$(NAME_LIB)

re: fclean all

.PHONY: all clean fclean re demo demo_main demo_posix demo_sigaction demo_kill demo_leak demo_zombie demo_shell demo_signals
.PHONY: test

-include $(DEP_LIB)