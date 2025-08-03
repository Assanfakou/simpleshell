/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:24:56 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/03 19:05:34 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"


void	create_pipe(t_cmd *cmd, int *nb_cmds, int *nb_pipes, int **pipes)
{
	*nb_cmds = count_cmds(cmd);
	*nb_pipes = *nb_cmds - 1;
	*pipes = create_pipes(cmd);
	if (!*pipes)
	{
		perror("failed to create pipes");
		free_t_cmd(cmd);
		exit(1);
	}
}

void	handle_redirection_error(t_cmd *temp)
{
	if (!temp->next)
		exit(1);
	else
		exit(0);
}

void check_path_is_null(t_cmd *temp , char *path, t_env **env, int *pipes)
{
	if (!path)
	{
		if (temp->argv && temp->argv[0])
		{
			write(2, "minishell: ", 11);
			write(2, temp->argv[0], ft_strlen(temp->argv[0]));
			write(2, ": command not found\n", 21);
		}
		cleaning_cmd_and_pipes(pipes, env);
		exit(127);
	}
}

void	prepare_path_and_exec(t_cmd *temp, t_env **env, int *pipes)
{
	char	*path;
	char	**envp;

	if (temp->argv[0][0] == '/' || (temp->argv[0][0] == '.'
			&& temp->argv[0][1] == '/'))
		path = ft_strdup(temp->argv[0]);
	else
		path = get_cmd_path(temp->argv[0], *env);
	check_path_is_null(temp , path, env, pipes);
	check_file(temp, path, env, pipes);
	envp = env_to_envp(*env);
	if (execve(path, temp->argv, envp) == -1)
	{
		perror("execve");
		cleaning_cmd_and_pipes(pipes, env);
		free(path);
		free_envp(envp);
		exit(126);
	}
}

void	pipe_executor(t_cmd *cmd, t_env **env)
{
	t_cmd	*temp;
	pid_t	pid;
	int *pipes;
	
	int (i), (nb_cmds), (nb_pipes);
	nb_cmds = count_cmds(cmd);
	nb_pipes = nb_cmds - 1;
	pipes = create_pipes(cmd);
	temp = cmd;
	i = 0;
	while (temp)
	{
		pid = fork();
		if (pid == 0)
		{
			handle_child_process(temp, i, pipes, nb_pipes);
			handle_child_helper(temp, pipes, env);
			free_t_cmd(cmd);
		}
		else if (pid < 0)
		{
			perror("fork failed");
			free_t_cmd(temp);
			free_t_env(*env);
			exit(1);
		}
		temp = temp->next;
		i++;
	}
	close_pipe_and_wait(nb_cmds , nb_pipes , pipes);
}
