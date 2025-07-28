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
    if (ft_strcmp(cmd->argv[0], "clear_env") == 0)  // reeeemove after use
		return (1);
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
        do_exit(cmd->argv);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        do_env(cmd->argv, env);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        do_export(cmd->argv, env);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        do_unset(cmd->argv, *env);
    else if (ft_strcmp(cmd->argv[0], "clear_env") == 0) // reeeemove after use
        free_env(env);
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
    
    // case: empty command with redirection only (like: > file)
    if (!cmd->argv || !cmd->argv[0])
    {
        int saved_stdout = dup(STDOUT_FILENO);
        find_redirection(cmd->redir);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        g_exit_status = 0; //7it t9der tkon ba9a chi value 9dima
        return;
    }
    if (cmd->argv && cmd->argv[0] && !get_cmd_path(cmd->argv[0], *env) && !is_builtin(cmd)) //handle user give input ma3ndoch m3na
    {
        write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
        write(2, ": command not found\n", 21);
        g_exit_status = 127;
        return;
    }
    
    if (ft_strlen(cmd->argv[0]) == 0) //handle case ""
    {
        printf("Command '' not found\n");
        g_exit_status = 127;
        return;
    }
    

//ask ali here 3lach kaykmel fchi case wkha kayna return darori khaso had order dyal if statemnt si non maykhdemch  

    // case: single builtin without pipe
    if (is_builtin(cmd) && !has_pipe(cmd))
    {
        int saved_stdout = dup(STDOUT_FILENO);
        find_redirection(cmd->redir);
        exec_builtin(cmd, env);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        return;
    }

    // else: pipeline or external command
    pipe_executor(cmd, env, envp);
}

void f_main(t_cmd *cmd, char **envp, t_env **env)
{
    for (int k = 0; cmd->argv && cmd->argv[k]; k++)
            printf("count cmd : %s ", cmd->argv[k]);
    printf("\n");
    executor(cmd, env, envp);
}

