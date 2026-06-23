CFLAGS		+= -std=c99 -pedantic -Wshadow -I../include -I./data_structures -I./ft_printf/include
DEPFLAGS	?= -MMD -MP
NAME_LIB	=		libds
NAME		=		$(NAME_LIB).a
LIB_DEPS	?= string memory stdio ctype
PROVIDES	?=
SRCDIR		:= .
SRCS		:= $(sort $(patsubst ./%,%,$(shell find $(SRCDIR) -type f -name '*.c')))
OBJ_DIR		?=	obj
OBJS		:=	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
DPDC		:=	$(OBJS:.o=.d)

-include $(DPDC)
include ../mk/common.mk
