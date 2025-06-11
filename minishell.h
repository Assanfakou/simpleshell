#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
typedef enum s_type
{
    T_HERDOC,
    T_OUTPUT,
    T_INPUT,
    T_PIPE,
    T_APPAND,
    T_WORD
}  t_type; 

typedef struct s_token {
    t_type     type; // type "T_input" "output" " word"
    char             *value; //"<" "|" "command"
    struct s_token   *next;
}   t_token;

typedef struct s_redir
{
    t_type type;
    char *filename;
    struct s_redir *next;
}   t_redir;

typedef struct s_cmd
{
    char **argv; // array of pointers to store commands with arguments 
    t_redir *redir; // list of rredirections if there any of them
    struct s_cmd *next; // if there is a pipe we creat another t_cmd to store the other arguments after the pipe
}   t_cmd;

int ft_isspace(char i);
int is_start_char(int c);
int is_var_char(int c);

t_token *create_token(char *str, int len, t_type type);
t_type token_type(char c, char next);
t_token *tokenize(char *line);
void add_token(t_token **head, t_token *new);
void print_token(t_token *token);
int parce_pipe_redi(char *line, int i, t_token **head);
int parce_d_s_quotes(char *line, int i, t_token **head);

void    ft_print_error(char *error);
void check_errors(t_token **head);

void free_t_token(t_token **head);

#endif
