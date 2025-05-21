#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

// typedef enum e_token_type {
//     T_WORD,
//     T_PIPE,
//     T_INPUT,
//     T_OUTPUT,
//     T_APPEND,
//     T_HERDOC
// }   t_token_type;

typedef struct s_token {
    char     *type;
    char             *value;
    struct s_token   *next;
}   t_token;

char *token_type(char c);
t_token *tokenize(char *line);
void add_token(t_token **head, t_token *new);
t_token *create_token(char *str, int len, char *type);
// int isspace(char i);
#endif
