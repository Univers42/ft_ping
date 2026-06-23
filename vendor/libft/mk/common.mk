# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    common.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 19:53:01 by                   #+#    #+#              #
#    Updated: 2025/12/11 15:00:39 by dlesieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════
# ║	Includes to add if we need other configurations                          ║
# ════════════════════════════════════════════════════════════════════════════

# Resolve includes relative to this makefile's directory so external callers work
MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILE_DIR)colors.mk
include $(MAKEFILE_DIR)symbols.mk

# ════════════════════════════════════════════════════════════════════════════
# ║    Variable compiler flags allow overiding                               ║
# ════════════════════════════════════════════════════════════════════════════

CC					?= cc
CFLAGS				= -std=c99 -pedantic -Wall -Wextra -Werror -MMD -g3 -O3 -I../include -I/../include/internals
CFLAGS_SHARED		?= -Wall -Werror -Wextra -Wnewline-eof -shared
INCLUDE_FLAGS		?= -I../include -I../include/internals
OUT					?= libft.so
LDFLAGS				?= -L. -lft -pthread -lm
AR					?= ar
ARFLAGS				?= rcs
RM					?= rm -f
SRCS				?= find . -name "**.c" 

# Directories
OBJ_DIR				?= obj
# BUILD_ROOT is the libft top-level dir (one level above mk/)
BUILD_ROOT			?= $(abspath $(MAKEFILE_DIR)/..)
# default build dir: <libft-root>/build (overrideable)
BUILD_DIR			?= $(BUILD_ROOT)/build
# directory for compiled test programs
BIN_DIR				?= $(BUILD_ROOT)/bin

# Logging state tokens and prefix
LOG_PREFIX			?= $(NAME)
STATE_INFO  	 	= INFO
STATE_WARN  	 	= WARN
STATE_OK    	 	= OK
STATE_NOTE  	 	= NOTE
STATE_ERROR 	 	= ERROR
STATE_DEBUG 	 	= DEBUG

# Test program configuration
TEST_PROGRAM		= test_program
TEST_SOURCES		= main.c

# compute short library name (strip leading "lib" if present) so "-l" flags are correct
LIBDIRS				:= alias bin build classes ctype data_structures debug glob ipc liblex math memory render sort stdio std strings termcap time var wctype
LIBNAME				:= $(basename $(notdir $(NAME)))
LIB_SHORT			:= $(if $(filter lib%,$(LIBNAME)),$(patsubst lib%,%,$(LIBNAME)),$(LIBNAME))
# link tests against archive located in BUILD_DIR by default
TEST_FLAGS			?= -L$(BUILD_DIR) -l$(LIB_SHORT)
# default list of available archives (caller can override LIB_LISTS or TEST_LIBS)
LIB_LISTS			?= $(abspath $(wildcard */build/*.a))
TEST_LIBS			?= $(LIB_LISTS)
# C++ compiler for .cpp tests (overrideable)
CXX					?= g++
# C++ flags (use when compiling .cpp tests)
CXXFLAGS			?= -std=c++17 -Wall -Wextra

# If a project declares LIB_DEPS (short names), produce link flags:
#   -L$(BUILD_DIR) -l<dep1> -l<dep2> ...
EXTRA_LIB_DEPS_LINKS ?= $(if $(strip $(LIB_DEPS)),-L$(BUILD_DIR) $(addprefix -l,$(LIB_DEPS)),)

# Addable dependencies (space-separated). Each entry may be:
#  - a directory name (e.g. "strings")
#  - a library short name (e.g. "string" -> libstring.a)
#  - a library filename (e.g. "libstring.a")
DEPS				?=
# Depth used by `find` can be adjusted if needed
DEP_SEARCH_DEPTH	?= 6

# New: directories (relative to SRCDIR) to exclude from recursive source search.
# Example in a module Makefile: DIR_EXCLUDE := input tests/old
DIR_EXCLUDE			?=

# New: ensure default exclusion of "input" and "tests" directories unless a module explicitly included them
# This prevents test/ or input/ trees from being picked up by the recursive find used to populate SRCS.
ifeq ($(findstring input,$(DIR_EXCLUDE)),)
	DIR_EXCLUDE := input $(DIR_EXCLUDE)
endif
ifeq ($(findstring tests,$(DIR_EXCLUDE)),)
	DIR_EXCLUDE := tests $(DIR_EXCLUDE)
endif

# Build a snippet to pass to `find` which prunes excluded directories.
# Note: modules should set SRCDIR before including common.mk so $(SRCDIR) is available.
FIND_EXCLUDE		:= $(foreach d,$(DIR_EXCLUDE), -path $(SRCDIR)/$(d) -prune -o)

# Helper that modules can use to get a list of .c sources while applying excludes.
# If SRCS is not defined by the module, common.mk will populate it using this.
FIND_SRCS			:= $(sort $(patsubst ./%,%,$(shell find $(SRCDIR) $(FIND_EXCLUDE) -type f -name '*.c')))

# If the module didn't declare SRCS, derive it using the above find-with-excludes.
ifeq ($(strip $(SRCS)),)
	SRCS := $(FIND_SRCS)
endif

# Debug flags
DEBUG_FLAGS			= -g3 -DDEBUG
SANITIZE_FLAGS		= -fsanitize=address -fsanitize=undefined
OPTIMIZE_FLAGS		= -O0
PROJECT				:= $(pwd)
COUNTER				= 0

# allow callers to override computed object lists
OBJS		?=		$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
DPDC		?=		$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.d))

# New: explicit archive paths for current lib and its declared LIB_DEPS.
# This helps with static linking order: include current lib archive first,
# then dependency archives explicitly (e.g. .../libstring.a .../libmemory.a .../libstd.a)
TEST_LIB_ARC        ?= $(BUILD_DIR)/lib$(LIB_SHORT).a
LIB_DEPS_ARCS       ?= $(if $(strip $(LIB_DEPS)),$(addprefix $(BUILD_DIR)/lib,$(addsuffix .a,$(LIB_DEPS))),)
# Additional set of archives to include (wildcard/other libs)
OTHER_LIB_ARCS      ?= $(TEST_LIBS)

# Group all archives so the static linker can resolve circular/transitive refs.
# Example expansion:
#   -Wl,--start-group $(TEST_LIB_ARC) $(LIB_DEPS_ARCS) $(OTHER_LIB_ARCS) -Wl,--end-group
LD_GROUP :=
ifeq ($(strip $(TEST_LIB_ARC) $(LIB_DEPS_ARCS) $(OTHER_LIB_ARCS)),)
	LD_GROUP :=
else
	LD_GROUP := -Wl,--start-group $(TEST_LIB_ARC) $(LIB_DEPS_ARCS) $(OTHER_LIB_ARCS) -Wl,--end-group
endif

# ════════════════════════════════════════════════════════════════════════════
# ║	utils functions to use to automatize more easily						 ║
# ════════════════════════════════════════════════════════════════════════════

# ════════════════════════════════════════════════════════════════════════════
# ║                           COMMON VARIABLES                               ║
# ════════════════════════════════════════════════════════════════════════════

# Ensure dependencies are available before archiving the current library.
# The deps target will build missing archives by locating directories and invoking make -C <dir> all.
.PHONY: deps
deps:
	@if [ -z "$(DEPS)" ]; then \
		printf '%s\n' "$(notdir $(CURDIR))[DEPS]: No external dependencies specified"; \
	else \
		for d in $(DEPS); do \
			orig="$$d"; \
			name=$$(basename "$$orig" .a); \
			name=$${name#lib}; \
			libfile="$(BUILD_DIR)/lib$${name}.a"; \
			if [ -f "$$libfile" ]; then \
				printf '%s\n' "$(notdir $(CURDIR))[DEPS]: Found $$libfile"; \
				continue; \
			fi; \
			dir=$$(find $(BUILD_ROOT) -maxdepth $(DEP_SEARCH_DEPTH) -type d -name "$$name" -print -quit); \
			if [ -n "$$dir" ]; then \
				printf '%s\n' "$(notdir $(CURDIR))[DEPS]: Building dependency $$name in $$dir..."; \
				$(MAKE) -C "$$dir" all || { printf '%s\n' "$(notdir $(CURDIR))[DEPS]: Failed to build $$name in $$dir"; exit 1; }; \
			else \
				printf '%s\n' "$(notdir $(CURDIR))[DEPS]: Dependency $$name not found under $(BUILD_ROOT)"; \
				exit 1; \
			fi; \
		done; \
	fi

# Ensure library dependencies declared by a project via LIB_DEPS are present.
.PHONY: ensure_lib_deps
ensure_lib_deps:
	@if [ -z "$(strip $(LIB_DEPS))" ]; then \
		$(call print_status,$(YELLOW),DEPS,No library dependencies specified); \
	else \
		$(call print_status,$(YELLOW),DEPS,Ensuring library dependencies are available...); \
		for dep in $(LIB_DEPS); do \
			libfile="$(BUILD_DIR)/lib$$dep.a"; \
			if [ -f "$$libfile" ]; then \
				$(call print_status,$(GREEN),DEPS,Found $$libfile); \
				continue; \
			fi; \
			dir=$$(find "$(BUILD_ROOT)" -maxdepth $(DEP_SEARCH_DEPTH) -type d -name "$$dep" -print -quit); \
			if [ -z "$$dir" ]; then \
				$(call print_status,$(RED),DEPS,Dependency $$dep not found under $(BUILD_ROOT)); \
				exit 1; \
			fi; \
			$(call print_status,$(CYAN),DEPS,Building dependency $$dep in $$dir...); \
			# ensure BUILD_DIR exists for marker files (no leading @ inside shell block) \
			mkdir -p "$(BUILD_DIR)"; \
			marker="$(BUILD_DIR)/.building-$$dep"; \
			# detect recursive build: if marker exists, skip to avoid cycle \
			if [ -f "$$marker" ]; then \
				$(call print_status,$(YELLOW),DEPS,Detected recursive build of $$dep - skipping (marker: $$marker)); \
				continue; \
			fi; \
			# create marker so nested invocations can detect recursion \
			touch "$$marker"; \
			# run child make; ensure marker removed on failure or success \
			if ! ($(MAKE) -C "$$dir" all); then \
				rm -f "$$marker"; \
				$(call print_status,$(RED),DEPS,Failed to build $$dep in $$dir); \
				exit 1; \
			fi; \
			rm -f "$$marker"; \
		done; \
	fi

# Main library rule: create archive and register provided short names (if any)
$(NAME): pre_build ensure_lib_deps $(OBJS)
	@$(call print_status,$(MAGENTA),ARCHIVE,Creating $(BUILD_DIR)/$(NAME)...)
	@mkdir -p $(BUILD_DIR)
	@$(AR) $(ARFLAGS) $(BUILD_DIR)/$(NAME) $(OBJS)
	@$(call print_status,$(GREEN),DONE,Library $(BUILD_DIR)/$(NAME) successfully created!)
	# If the library Makefile declared PROVIDES (space-separated short names),
	# create/update symlinks in BUILD_DIR: lib<short>.a -> $(NAME)
	@if [ -n "$(strip $(PROVIDES))" ]; then \
		src="$(BUILD_DIR)/$(NAME)"; \
		for p in $(PROVIDES); do \
			target="$(BUILD_DIR)/lib$$p.a"; \
			if [ "$$src" != "$$target" ]; then \
				ln -sf "$$src" "$$target"; \
			fi; \
		done; \
		$(call print_status,$(CYAN),PROVIDE,Registered $(strip $(PROVIDES)) -> $(BUILD_DIR)/$(NAME)); \
	fi

# Object compilation rule
# compile source (possibly in subdirs) into corresponding $(OBJ_DIR)/%.o
$(OBJ_DIR)/%.o : %.c
	@$(call create_dirs)
	@mkdir -p $(dir $@)
	@$(call print_status, $(CYAN), COMPILE, Compiling $< -> $@)
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(DEPFLAGS) -MF $(patsubst %.o,%.d,$@) -c $< -o $@

# Tests: compile each source in tests/ into $(BIN_DIR)/<name>
TEST_SRCS := $(sort $(wildcard tests/*.c) $(wildcard tests/*.cpp))
TEST_BINS := $(patsubst %.c,$(BIN_DIR)/%,$(notdir $(TEST_SRCS)))
TEST_BINS := $(patsubst %.cpp,$(BIN_DIR)/%,$(TEST_BINS))

# Extract include flags (e.g. -I...) so we don't pass -std=... from CFLAGS to g++
INCLUDES := $(filter -I%,$(CFLAGS) $(INCLUDE_FLAGS))

# Ensure test dependencies when requested (parse-time conditional)
.PHONY: ensure_test_deps
ensure_test_deps:
ifeq ($(strip $(TEST_DEPS)),)
	@$(call print_status,$(YELLOW),DEPS,No test dependencies specified)
else
	@$(call print_status,$(YELLOW),DEPS,Ensuring test dependencies are available...)
	@$(MAKE) --no-print-directory DEPS="$(TEST_DEPS)" deps || exit 1
endif

# Build tests: if there are no test sources, print a short message (parse-time).
ifeq ($(strip $(TEST_SRCS)),)
.PHONY: build_tests
build_tests:
	@$(call print_status,$(YELLOW),TESTS,No tests found in tests/)
else
.PHONY: build_tests
build_tests: ensure_test_deps
	@$(call print_status,$(BLUE),TESTS,Building test programs into $(BIN_DIR)...)
	@mkdir -p $(BIN_DIR)
	@if [ -z "$(TEST_SRCS)" ]; then \
		$(call print_status,$(YELLOW),TESTS,No tests found in tests/); \
	else \
		for src in $(TEST_SRCS); do \
			name=$$(basename $$src); \
			out=$(BIN_DIR)/$${name%.*}; \
			ext=$${name##*.}; \
			$(call print_status,$(CYAN),COMPILE,Compiling $$src -> $$out); \
			if [ "$$ext" = "cpp" ]; then \
				$(CXX) $(CXXFLAGS) $(INCLUDES) $$src $(TEST_FLAGS) $(LD_GROUP) -o $$out || exit 1; \
			else \
				$(CC) $(CFLAGS) $$src $(TEST_FLAGS) $(LD_GROUP) -o $$out || exit 1; \
			fi; \
		done; \
	fi
endif

# Default target
all: $(NAME)

# Clean rules
clean:
	@$(call clean_objects)

fclean: clean
	@$(call print_status, $(RED), CLEAN, Removing archive and test binary...)
	@$(RM) $(BUILD_DIR)/$(NAME)
	@rm -rf $(BIN_DIR) $(BIN_DIR)/*
	@$(RM) $(BIN_DIR)

re: fclean all

# Main test target: explicitly build library, then tests, (do not run binaries automatically).
test: $(NAME)
	@$(call print_status,$(CYAN),TEST,Building test programs...)
	@$(MAKE) --no-print-directory build_tests
	@$(call print_status,$(GREEN),TEST,Test binaries created in $(BIN_DIR). Run 'make run_tests' to execute them.)

.PHONY: run_tests
run_tests: $(NAME)
	@$(call print_status,$(CYAN),TEST,Running test programs...)
	@$(MAKE) --no-print-directory build_tests
	@$(call print_status,$(GREEN),TEST,Executing test binaries:)
	@for tb in $(TEST_BINS); do \
		if [ -x "$$tb" ]; then \
			$$tb; \
		else \
			$(call print_status,$(YELLOW),TEST,Skipping $$tb (not found or not executable)); \
		fi; \
	done

# Unit test target
unit_test: $(NAME)
	@$(call print_status,$(BLUE),UNIT_TEST,Running unit tests...)
	@for test in tests/*.c; do \
		if [ -f "$$test" ]; then \
			$(CC) $(CFLAGS) "$$test" $(TEST_FLAGS) -o test_runner; \
			./test_runner; \
			$(RM) test_runner; \
		fi; \
	done

# Memory test with valgrind
valgrind: $(NAME) $(TEST_SOURCES)
	$(call print_status,$(YELLOW),VALGRIND,Running memory checks...)
	@$(CC) $(CFLAGS) -g3 $(TEST_SOURCES) $(TEST_FLAGS) -o $(TEST_PROGRAM)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_PROGRAM)

# Performance test
benchmark: $(NAME) $(TEST_SOURCES)
	$(call print_status,$(MAGENTA),BENCHMARK,Running performance tests...)
	@$(CC) $(CFLAGS) -O3 $(TEST_SOURCES) $(TEST_FLAGS) -o $(TEST_PROGRAM)
	@time ./$(TEST_PROGRAM)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS)
debug: all
	$(call print_status,$(YELLOW),DEBUG,Debug mode enabled)

# Debug with sanitizers
debug_sanitize: CFLAGS += $(DEBUG_FLAGS) $(SANITIZE_FLAGS) $(OPTIMIZE_FLAGS)
debug_sanitize: all
	$(call print_status,$(YELLOW),DEBUG,Debug mode with sanitizers enabled)

# Clean test artifacts
clean_test:
	$(call print_status,$(RED),CLEAN,Removing test artifacts...)
	@$(RM) $(TEST_PROGRAM) test_runner

# Release build
release: CFLAGS += -O3 -DNDEBUG
release: all
	$(call print_status,$(GREEN),RELEASE,Release mode enabled)

# Profile build
profile: CFLAGS += -pg -O2
profile: all
	$(call print_status,$(BLUE),PROFILE,Profile mode enabled)

# Static analysis
analyze:
	$(call print_status,$(CYAN),ANALYZE,Running static analysis...)
	@cppcheck --enable=all --std=c99 $(SRC_DIRS) 2>/dev/null || true
	@scan-build make fclean all 2>/dev/null || true

.PHONY: analyze profile release debug_sanitize debug pre_build all clean fclean re clean_test benchmark valgrind unit_test test