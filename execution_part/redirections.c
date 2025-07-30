#include "execution/execution.h"

int check_fd(int fd, t_redir *redir)
{
    if (fd < 0)
    {
        write(2, "minishell: ", 12);
        perror(redir->filename);
        return (1);
    }
    return (0);
}
void dup_fd_out(int fd)
{
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 failed");
        close(fd);
        exit(1);
    }
}
void dup_fd_inp(int fd)
{
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2 failed");
        close(fd);
        exit(1);
    }
}

void handle_heardoc(char *filename)
{
    int pipefd[2];
    pipe(pipefd);

    while (1)
    {
        char *line = readline("> ");
        if (ft_strcmp(line, filename) == 0)
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);

    dup_fd_inp(pipefd[0]); //kanbdlo stdin bpipefd[0] ywli y9ra mn pipe
    close(pipefd[0]);
}

int find_redirection(t_redir *redir)
{
    int fd;

    while(redir)
    {
        if (redir->type == R_INPUT) //fach kandiro wc < main.c matalan rah hna kanchdo stdin kanbdloh bfd dyala main.c bach y9ra mno sf!!!!!!!!
        {   
            fd = open(redir->filename, O_RDONLY);
            if (check_fd(fd, redir))
                return (1);
            dup_fd_inp(fd); //kanbdlo stdin ywli y9ra mn fd li 7at lih
            close(fd);
        }
        else if (redir->type == R_OUTPUT)
        {
            fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644); //trunc kat7iyd dakchi l9dim okatkteb jdid
            if (check_fd(fd, redir))
                return (1);
            dup_fd_out(fd); // stdout ywli yktb f fd li 3titi (ex: file)
            close(fd);
        }
        else if (redir->type == R_APPAND)
        {
            fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (check_fd(fd, redir))
                return (1);
            dup_fd_out(fd); //stdout ywli yktb f fd (lfer9 bin hadi oR_output anaho hadi katzid ktabta fo9 l9idma lakhra la)
            close(fd);
        }
        // else if (redir->type == R_HERDOC)
        //     handle_heardoc(redir->filename);
        redir = redir->next;
    }
    return (0);   
}



