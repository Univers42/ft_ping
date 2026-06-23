# **************************************************************************** #
#                                                                              #
#    ft_ping — recode of the inetutils ping (42 project)                       #
#                                                                              #
# **************************************************************************** #

NAME        := ft_ping

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

LIBFT_DIR   := vendor/libft
LIBFT       := $(LIBFT_DIR)/build/lib/libft.a

CPPFLAGS    := -Iinclude -I$(LIBFT_DIR)/include -I$(LIBFT_DIR) -D_GNU_SOURCE

SRCDIR      := src
OBJDIR      := obj
HEADER      := include/ft_ping.h

SRCS        := main.c args.c args2.c usage.c dns.c net.c sockopt.c ipts.c \
               checksum.c send.c recv.c loop.c flood.c pattern.c print.c \
               stats.c signal.c util.c
OBJS        := $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

# libft is an order-only prerequisite: rebuilding the archive must not relink
# ft_ping unless an object actually changed.
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

# Link the static archive by path: only the objects ft_ping references are
# pulled in (the prebuilt libft.so carries unrelated undefined symbols).
$(NAME): $(OBJS) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# 42 norm check on project sources only (libft has its own verif_norm).
# Fail on real violations (Error!); the lone GLOBAL_VAR notice on the signal
# flag is permitted and justified, so notices/OK do not fail the gate.
norm:
	@norminette include src | grep 'Error' && exit 1 || echo "norm: clean"

# project-scoped static analysis (the kit gate scans vendored libft too).
lint:
	@cppcheck --enable=warning,style --error-exitcode=1 --quiet include src

bench: all
	@sh bench/run.sh

.PHONY: all clean fclean re norm lint bench
