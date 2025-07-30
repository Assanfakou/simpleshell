#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "../../libft/libft.h"
#include "../builtins/builtins.h"
#include "../../lexer/parce.h"
#include "../../lexer/lexer.h"


//execute_external
char *get_cmd_path(char *cmd, t_env *env);
char **env_to_envp(t_env *env);

//pipe_executor
void pipe_executor(t_cmd *cmd, t_env **env, char **envp);

//find_redirection
int find_redirection(t_redir *redir);

//main
int is_builtin(t_cmd *cmd);
int exec_builtin(t_cmd *cmd, t_env **env);

#endif
