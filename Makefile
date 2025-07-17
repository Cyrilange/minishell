NAME        = minishell

LIBFT       = ./includes/libft

CC          = cc # it has to be cc, not gcc
CFLAGS      = -g -Wall -Wextra -I$(LIBFT) -I./includes
LDFLAGS     = -lreadline


SRC_DIR     = ./src
OBJ_DIR     = ./obj

# List source files with path
SRC_FILES = \
	src/main.c \
	src/built_ins/builtins.c \
	src/built_ins/cd.c \
	src/built_ins/pwd.c \
	src/built_ins/echo.c \
	src/built_ins/env.c \
	src/built_ins/exit.c \
	src/built_ins/export_and_unset.c \
	src/miniutils/matrix_str.c \
	src/miniutils/errors.c \
	src/parsing/condition_while_pipe.c \
	src/parsing/handle_redirection.c \
	src/executor/opening_minishell.c \
	src/parsing/tokenise.c \
	src/parsing/handle_heredoc.c \
	src/parsing/helper_small_function.c \
	src/parsing/pipe_helper.c \
	src/parsing/variables.c \
	src/parsing/variables_helper.c \
	src/parsing/helper_parse.c \
	src/parsing/pipes.c \
	src/executor/redirections.c \
	src/executor/search_binary.c \

# Convert source files into object files
OBJS        = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

# Rule to build final executable
$(NAME): $(OBJS) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)/libft.a $(LDFLAGS)


# Rule to build libft
$(LIBFT)/libft.a:
	@$(MAKE) -C $(LIBFT)

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean

# Clean all
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
