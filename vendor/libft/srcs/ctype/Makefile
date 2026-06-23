# project-specific settings (variables kept overrideable)
CFLAGS += -std=c99 -pedantic -Wshadow
# Add include paths for public and internal headers if they exist
ifneq ($(wildcard ../include),)
CFLAGS += -I../include
endif
ifneq ($(wildcard ../include/internals),)
CFLAGS += -I../include/internals
endif
CFLAGS += -I../ctype -I./ft_printf/include

# Generate gcc deps: .d files next to .o
DEPFLAGS ?= -MMD -MP

NAME_LIB	=		libctype
NAME		=		$(NAME_LIB).a

# ctype uses ft_strchr from string module
LIB_DEPS	?= string

# Provide short-name(s) so common.mk will register libctype.a in BUILD_DIR
PROVIDES	?=	ctype

# collect ONLY .c files directly in ctype/ using -maxdepth 1
SRCDIR := .
SRCS := $(sort $(patsubst ./%,%,$(shell find $(SRCDIR) -maxdepth 1 -type f -name '*.c')))

OBJ_DIR		?=	obj

OBJS		:=	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
DPDC		:=	$(OBJS:.o=.d)

-include $(DPDC)

include ../mk/common.mk
