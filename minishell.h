#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef enum e_token_type {
    T_WORD,
    T_PIPE,
    T_INPUT,
    T_OUTPUT,
    T_APPEND,
    T_HEREDOC
}   t_token_type;

typedef struct s_redir {
    t_token_type     type;
    char             *file;
    struct s_redir   *next;
}   t_redir;

typedef struct s_cmd {
    char         **argv;
    t_redir      *redir;
    struct s_cmd *next;
}   t_cmd;

#endif
