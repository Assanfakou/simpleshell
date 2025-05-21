#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

// < input > output 
// << herdok >> appand

/*
* to parse by this linked list
* using the type to store what kind of koken i got word or input pipe
* value to store the actual token
* next to the other token i'll get next
*/

typedef struct s_token {
    char     *type; // type "T_input" "output" " word"
    char             *value; //"<" "|" "command"
    struct s_token   *next;
}   t_token;

typedef struct s_redir
{
    char *type;
    char *file;
    struct s_redir *next;
}   t_redir;

typedef struct s_cmd
{
    char **argv;
    t_redir *redir;
    struct s_cmd *next;
}   t_cmd;

char *token_type(char c, char next);
t_token *tokenize(char *line);
void add_token(t_token **head, t_token *new);
t_token *create_token(char *str, int len, char *type);
int ft_isspace(char i);
#endif
