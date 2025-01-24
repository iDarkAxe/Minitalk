.PHONY : all clean fclean re
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
CFLAGS_DEBUG = $(CFLAGS) -g3 -fsanitize=address -fsanitize=leak -Weverything -Wno-unsafe-buffer-usage #use CC=clang
NAME = libftprintf.a

# DIRECTORIES
P_INC = ./
P_SRC = ./
P_OBJ = .obj/
P_LIBFT = libft/

# FILES
INC = ft_printf.h
SRC =  ft_printf.c
SRC_LIB = ft_putnbr_base.c ft_putstr_fd.c ft_strlen.c

# MANIPULATION
SRCS =	$(addprefix $(P_SRC), $(SRC) $(SRC_LIB))

OBJS = $(subst $(P_SRC), $(P_OBJ), $(SRCS:.c=.o))

P_OBJS = $(subst $(P_SRC), $(P_OBJ), $(P_SRC))
DEPS = $(OBJS:%.o=%.d)

# RULES
all :$(NAME)

$(NAME): $(P_OBJ)$(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(P_OBJ)%.o : %.c | $(P_OBJS)
	$(CC) $(CFLAGS) -c $< -I $(P_INC) -o $@

$(P_OBJS) : 
	mkdir -p $(P_OBJS)

# CLEAN SECTION
clean :
	rm -rfd $(P_OBJ)

fclean : clean
	rm -rf $(NAME)

re : 
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)