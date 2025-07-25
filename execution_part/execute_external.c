#include "execution/execution.h"

void free_split_content(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
        free(array[i++]);
    free(array);
}
char *get_cmd_path(char *cmd)
{
    int i;
    char *chunk;
    char *full_path;
    char **paths;
    
    paths = ft_split(getenv("PATH"), ':');
    full_path = NULL;
    i = 0;
    while (paths && paths[i])
    {
        chunk = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(chunk, cmd);
        free(chunk);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        i++;
    }
    free_split_content(paths);
    return (full_path);
}

void execute_external(t_cmd *cmd, char **envp)
{
    char *path = get_cmd_path(cmd->argv[0]);
    pid_t pid;

    if (path != NULL)
    {
        pid = fork();
        if (pid == 0)
        {
            find_redirection(cmd->redir);
            execve(path, cmd->argv, envp);
            perror("execve failed");
            exit(127);
        }
        else if (pid > 0)
            waitpid(pid, NULL, 0);
        else
            perror("fork failed");
        free(path);
    }
    else
    {
        if (cmd->argv && cmd->argv[0])
        {
            printf("%s: command not found\n", cmd->argv[0]);
            g_exit_status = 127000;
        }

    }
}
