.PHONY: all clean fclean re bonus debug debug-cc debug-print
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
DEPENDENCIES = -MMD -MP
NO_DIR = --no-print-directory
MAKE := $(MAKE) $(NO_DIR)
NAME = server
SNAME = client
LDFLAGS = -L$(P_LIB) -lftprintf

# Debugging flags
CFLAGS_DEBUG = -Wall -Wextra -g3 -D DEBUG=1
CC_DEBUG = clang
CC_DEBUG_CFLAGS = -g3 -DDEBUG=1 -Weverything -pedantic -O2 -Wwrite-strings -Wconversion -Wno-disabled-macro-expansion -fsanitize=address -fsanitize=leak

# Directories
P_SRC = src/
P_CLIENT = client/

P_OBJ = .obj/
P_INC = inc/
P_LIB = lib/

# Source files
SRC_SERVER = \
	server.c
SRC_CLIENT = \
	client.c 
SRC_CLIENT_BONUS = \
	client_bonus.c \
	bonus.c

# Source files with paths
SRCS_SERVER = $(addprefix $(P_SRC), $(SRC_SERVER))
SRCS_CLIENT = $(addprefix $(P_SRC)$(P_CLIENT), $(SRC_CLIENT))
SRCS_CLIENT_BONUS = $(addprefix $(P_SRC)$(P_CLIENT), $(SRC_CLIENT))

# Object and dependency files
OBJS_SERVER = $(subst $(P_SRC), $(P_OBJ), $(SRCS_SERVER:.c=.o))
OBJS_CLIENT = $(subst $(P_SRC), $(P_OBJ), $(SRCS_CLIENT:.c=.o))
OBJS_CLIENT_BONUS = \
	$(addprefix $(P_OBJ), $(SRCS_CLIENT:.c=.o))\
	$(addprefix $(P_OBJ), $(SRCS_CLIENT_BONUS:.c=.o))
DEPS_SERVER = $(OBJS_SERVER:.o=.d)
DEPS_CLIENT = $(OBJS_CLIENT:.o=.d)

# Header files
INCS = $(addprefix $(P_INC), ft_printf.h)

# Targets
all: $(NAME) $(SNAME)

$(NAME): $(OBJS_SERVER) $(P_LIB)libftprintf.a
	$(MAKE) $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -I $(P_INC) -o $@ $(LDFLAGS)

$(SNAME): $(OBJS_CLIENT) $(P_LIB)libftprintf.a
	$(MAKE) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -I $(P_INC) -o $@ $(LDFLAGS)

$(P_OBJ)%.o: $(P_SRC)%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPENDENCIES) -I $(P_INC) -c $< -o $@

$(P_LIB)libftprintf.a:
	@$(MAKE) -C ft_printf
	@mkdir -p $(P_LIB)
	cp ft_printf/libftprintf.a $(P_LIB)
	cp ft_printf/ft_printf.h $(P_INC)

bonus :
	@$(MAKE) $(NAME)
	@$(MAKE) $(SNAME) SRC_CLIENT="$(SRC_CLIENT_BONUS)"

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
