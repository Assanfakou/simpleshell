#include "execution.h"
#include "main.h"


int is_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;

    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "env") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "export") == 0)
        return 1;
    if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return 1;

    return 0;
}
void exec_builtin(t_cmd *cmd, t_env **env)
{
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        do_cd(cmd->argv, *env);
    else if (ft_strcmp(cmd->argv[0], "echo") == 0)
        do_echo(cmd->argv, *env);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        do_pwd(cmd->argv, *env);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        do_exit(cmd->argv, &g_exit_status);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        do_env(cmd->argv, env);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        do_export(cmd->argv, env);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        do_unset(cmd->argv, *env);
}

int has_pipe(t_cmd *cmd)
{
    if (cmd && cmd->next != NULL)
        return (1);
    else
        return (0);
}

void executor(t_cmd *cmd, t_env **env, char **envp)
{
    if (!cmd)
        return;

    if (has_pipe(cmd))
        pipe_executor(cmd, envp);
    else if (is_builtin(cmd))
    {
        find_redirection(cmd->redir);

        exec_builtin(cmd, env);
    }
    else
    {
        execute_external(cmd, envp);
    }
}

void f_main(t_cmd *cmd, char **envp, t_env **env)
{
    // t_env *env = NULL;



    // env = create_env(envp);
    executor(cmd, env, envp);
    //print_env(env);
}

