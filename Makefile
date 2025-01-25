.PHONY: all clean fclean re bonus debug debug-cc debug-print
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEPENDENCIES = -MMD -MP
NAME = server
SNAME = client
LDFLAGS = -L$(P_LIB) -lftprintf

# Debugging flags
CFLAGS_DEBUG = -Wall -Wextra -g3 -DDEBUG=1
CC_DEBUG = clang
CC_DEBUG_CFLAGS = -g3 -DDEBUG=1 -Weverything -Wno-padded -pedantic -O2 -Wwrite-strings -Wconversion -fsanitize=address -fsanitize=leak

# Directories
P_SRC = src/
P_OBJ = .obj/
P_INC = inc/
P_LIB = lib/

# Source files
SRC_SERVER = server.c
SRC_CLIENT = client.c

# Object and dependency files
OBJS_SERVER = $(addprefix $(P_OBJ), $(SRC_SERVER:.c=.o))
OBJS_CLIENT = $(addprefix $(P_OBJ), $(SRC_CLIENT:.c=.o))
DEPS_SERVER = $(OBJS_SERVER:.o=.d)
DEPS_CLIENT = $(OBJS_CLIENT:.o=.d)

# Header files
INCS = $(addprefix $(P_INC), ft_printf.h)

# Targets
all: $(P_LIB)libftprintf.a 
	@mkdir -p $(P_OBJ) $(P_OBJ)/client $(P_OBJ)/server
	cc -g3 -Wextra -Wall src/server.c -o server -Llib -lftprintf -I inc
	cc -g3 -Wextra -Wall -c src/client/ft_atoi.c -o .obj/client/ft_atoi.o -I inc
	cc -g3 -Wextra -Wall src/client/client.c -o client -Llib -lftprintf -I inc

bonus:
	@mkdir -p $(P_OBJ) $(P_OBJ)/client $(P_OBJ)/server
	cc -g3 -Wextra -Wall src/server.c -o server -Llib -lftprintf -I inc
	cc -g3 -Wextra -Wall -c src/client/ft_atoi.c -o .obj/client/ft_atoi.o -I inc
	cc -g3 -Wextra -Wall -c src/client/bonus.c -o .obj/client/bonus.o -I inc
	cc -g3 -Wextra -Wall src/client/client_bonus.c -o client .obj/client/bonus.o -Llib -lftprintf -I inc

# all: $(NAME) $(SNAME)

$(NAME): $(OBJS_SERVER) $(P_LIB)libftprintf.a
	$(CC) $(CFLAGS) $(OBJS_SERVER) -I $(P_INC) -o $@ $(LDFLAGS)

$(SNAME): $(OBJS_CLIENT) $(P_LIB)libftprintf.a
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -I $(P_INC) -o $@ $(LDFLAGS)

$(P_OBJ)%.o: $(P_SRC)%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPENDENCIES) -I $(P_INC) -c $< -o $@

$(P_LIB)libftprintf.a:
	@$(MAKE) -C ft_printf
	@mkdir -p $(P_LIB)
	cp ft_printf/libftprintf.a $(P_LIB)
	cp ft_printf/ft_printf.h $(P_INC)

# Cleaning rules
clean:
	rm -rf $(P_OBJ)

clean-bin:
	rm -f $(NAME) $(SNAME)

clean-lib:
	rm -rf $(P_LIB)

fclean: clean clean-bin clean-lib
	@$(MAKE) -C ft_printf fclean

re: fclean all

# Debugging rules
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: re

debug-cc: CC=$(CC_DEBUG)
debug-cc: CFLAGS=$(CC_DEBUG_CFLAGS)
debug-cc: re

# Include dependency files
-include $(DEPS_SERVER) $(DEPS_CLIENT)
