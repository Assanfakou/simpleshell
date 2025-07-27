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


// extern int g_exit_status; //bach tlinka fga3 files li m7tajinha 


//execute_external
void execute_external(t_cmd *cmd, t_env **env);
char *get_cmd_path(char *cmd, t_env *env);
char **env_to_envp(t_env *env);
//pipe_executor
void pipe_executor(t_cmd *cmd, t_env **env, char **envp);

//find_redirection
void find_redirection(t_redir *redir);

//main
int is_builtin(t_cmd *cmd);
void exec_builtin(t_cmd *cmd, t_env **env);


void	free_env(t_env **env); //remove after use
#endif
