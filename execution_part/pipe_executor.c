#include "execution/execution.h"
#include <errno.h>

int count_cmds(t_cmd *cmd)
{
    int count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return count;
}

int *create_pipes(t_cmd *cmd)
{
    int nb_cmd = count_cmds(cmd);
    int nb_pipes = nb_cmd - 1;
    int *pipes = malloc(sizeof(int) * nb_pipes * 2); //2 mean read and write
    if (!pipes)
        return (NULL);

    int i = 0;
    while (i < nb_pipes)
    {
        if (pipe(&pipes[i * 2]) < 0) //pipe() → katsayb file descriptors -> Katkhlli lfd (file descriptors) f array omakadir walo
        {
            perror("pipe failed");
            free(pipes);
            return NULL;
        }
        i++;
    }
    return (pipes);
}

void close_pipe_and_wait(int nb_cmds, int nb_pipes, int *pipes)
{
    // parent: close pipes
    int i = 0;
    while (i < nb_pipes * 2)
        close(pipes[i++]);

    int status;
    int j = 0;
    while (j < nb_cmds)
    {
        wait(&status);
        if (WIFEXITED(status)) // hadi macro f C, katcheck wach dak child tsala normal (b exit(x)), mashi b signal (kill, segfault...).
            g_exit_status = WEXITSTATUS(status); // ila hya true, n9adro njibo exit status dyal command.
        j++;
    }

    free(pipes);
}

int has_output_redirection(t_cmd *cmd)
{
    t_redir *r = cmd->redir;
    while (r)
    {
        if (r->type == R_OUTPUT || r->type == R_APPAND)
            return 1;
        r = r->next;
    }
    return 0;
}


void pipe_executor(t_cmd *cmd, t_env **env, char **envp)
{
    //printf("again/n");
    int nb_cmds = count_cmds(cmd);
    int nb_pipes = nb_cmds - 1;
    int *pipes = create_pipes(cmd);
    if (!pipes)
    {
        perror("failed to create pipes");
        return;
    }

    t_cmd *temp = cmd;
    int i = 0;

    while (temp)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            int j = 0;
            
            if (i != 0)
                dup2(pipes[(i - 1) * 2], STDIN_FILENO);
            if (temp->next && !has_output_redirection(temp))
                dup2(pipes[i * 2 + 1], STDOUT_FILENO);
            // Close all pipes
            while (j < nb_pipes * 2) //*2 mean read write
                close(pipes[j++]);

            find_redirection(temp ->redir);

            if (is_builtin(temp))
            {
                exec_builtin(temp, env);
                exit(0); //ykhrej ghir child (kol child yexecute one cmd only)
            }
            // Command path resolution
            char *path = NULL;
            if (temp->argv[0][0] == '/' ||
                (temp->argv[0][0] == '.' && temp->argv[0][1] == '/'))
                path = ft_strdup(temp->argv[0]); //copy of path
            else
                path = get_cmd_path(temp->argv[0], *env);  // search in PATH
            if (!path) // path b9a khawi
            {
                if (temp->argv && temp->argv[1])
                {
                    printf("hereee\n");
                    write(2, temp->argv[1], ft_strlen(temp->argv[1]));
                    write(2, ": command not found\n", 21);
                } 
                if (temp->argv && temp->argv[0])
                {
                    write(2, temp->argv[0], ft_strlen(temp->argv[0]));
                    write(2, ": command not found\n", 21);
                }
                g_exit_status = 127;
                
                exit(127);

            }
            // Error: permission denied
            if (access(path, F_OK) == 0 && access(path, X_OK) != 0) //F_OK mean if exesist
            {
                printf("%s: Permission denied\n", path);
                free(path);
                exit(126);
            }
            // Exec external command
            execve(path, temp->argv, envp); //execve katbdlk process kaml b chi command (par exemple ls). 
            // argv → tableau li fih: argv[0] = "ls" ,argv[1] = "-l", argv[2] = NULL
            if (execve(path, temp->argv, envp) == -1) //check that in linux
            {
                printf("errno = %d\n", errno);
                if (errno == ENOEXEC)
                {
                    write(2, "minishell: ", 11);
                    write(2, path, ft_strlen(path));
                    write(2, ": Exec format error\n", 21);
                    free(path);
                    exit(126);
                }
                else if (errno == EACCES)
                {
                    write(2, "minishell: ", 11);
                    write(2, path, ft_strlen(path));
                    write(2, ": Permission denied\n", 21);
                    free(path);
                    exit(126);
                }
                else
                {
                    write(2, "minishell: ", 11);
                    perror(path);
                    free(path);
                    exit(127);
                }
            }
        }
        else if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }
        temp = temp->next;
        i++;
    }
    close_pipe_and_wait(nb_cmds, nb_pipes, pipes); //close 3la hsab parent wkha closina fchild khasna nzido hna
}

