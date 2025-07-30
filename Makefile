CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3 #-fsanitize=addressi
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = execution_part/builtins/do_cd.c execution_part/builtins/do_echo.c execution_part/builtins/do_env.c execution_part/builtins/do_exit.c execution_part/builtins/do_export.c \
	execution_part/builtins/do_pwd.c execution_part/builtins/do_unset.c execution_part/builtins/print_env.c execution_part/builtins/create_env.c \
 lexer/exit_status.c execution_part/utils.c execution_part/redirections.c execution_part/pipe_executor.c execution_part/execution/main.c lexer/error.c lexer/expand.c lexer/lexer_help.c lexer/main.c lexer/parce.c lexer/t_cmd_helpers.c lexer/token_help.c lexer/tokenizing.c \
	execution_part/execution/free_env.c lexer/signals.c lexer/herdoc_handler.c



OBJ = $(SRC:%.c=%.o)
NAME = minishell
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


clean:
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re bonus
