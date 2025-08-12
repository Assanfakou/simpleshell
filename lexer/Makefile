SCC = cc
CFLAGS = #-Wall -Wextra -Werror -ggdb3 -g3
LINKERS = -L ../libft -lft -lreadline 

SRC_FILES= ../signals.c error.c exit_status.c expand.c herdoc_parser.c lexer_help.c main.c parce.c t_cmd_helpers.c token_help.c tokenizing.c ast_print/ast_print.c ast_print/ast_print_utils.c ast_print/ast_type_to_str.c createnv.c lexer/wild_card.c
SRC_OBJ= $(SRC_FILES:%.c=%.o)
LIBFT_DIR= ../libft
libft_rule = ../libft/libft.a

NAME=minishell

all: $(NAME)

$(libft_rule):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJ) $(libft_rule) 
	$(CC) $(SRC_OBJ) $(LINKERS) -o $(NAME)

clean: 
	$(RM) $(SRC_OBJ) $(OBJ_BONUS)
	$(MAKE) -s -C $(LIBFT_DIR) clean

fclean:
	$(RM) $(SRC_OBJ) $(NAME) 
	$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all libft_rule clean fclean re
.SECONDARY: $(SRC_OBJ)
