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
        do_exit(cmd->argv);
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
    int saved_stdout;

    if (!cmd)
        return;
    
    if ((!cmd->argv || !cmd->argv[0]))  //secod mean allocated but set 1 in len (null)
    {
        saved_stdout = dup(STDOUT_FILENO);         // 1. Save stdout
        find_redirection(cmd->redir);              // 2. Apply redirection
        dup2(saved_stdout, STDOUT_FILENO);         // 3. Restore stdout
        close(saved_stdout);                       // 4. Clean up
        return;
    }

    if (is_builtin(cmd))
    {
        if (has_pipe(cmd))
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                pipe_executor(cmd, env, envp);
                return;
            }
            else
                waitpid(pid, NULL, 0);
        }
        else
        {
            saved_stdout = dup(STDOUT_FILENO);         
            find_redirection(cmd->redir);              // 2. Apply redirection (if any)
            exec_builtin(cmd, env);                    
            dup2(saved_stdout, STDOUT_FILENO);         
            close(saved_stdout);                      
            return;
        }
    }
    else
        execute_external(cmd, envp);

    // char *path = get_cmd_path(cmd->argv[0]);
    // if (!path)
    // {
    //     printf("❌ DEBUG: %s not found in PATH\n", cmd->argv[0]);
    //     exit(127);
    // }
    // else
    // {
    //     printf("✅ DEBUG: %s resolved as: %s\n", cmd->argv[0], path);
    //     execve(path, cmd->argv, envp);
    //     perror("execve failed ❌");
    //     exit(1);
    // }
}


void f_main(t_cmd *cmd, char **envp, t_env **env)
{
    
    executor(cmd, env, envp);
}

