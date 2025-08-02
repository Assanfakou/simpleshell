/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:24:56 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/02 18:52:18 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	create_pipe(t_cmd *cmd, int *nb_cmds, int *nb_pipes, int **pipes)
{
	*nb_cmds = count_cmds(cmd);
	*nb_pipes = *nb_cmds - 1;
	*pipes = create_pipes(cmd);
	if (!*pipes)
	{
		perror("failed to create pipes");
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

void	prepare_path_and_exec(t_cmd *temp, t_env **env, int *pipes)
{
	char	*path;
	char	**envp;

	if (temp->argv[0][0] == '/' || (temp->argv[0][0] == '.'
			&& temp->argv[0][1] == '/'))
		path = ft_strdup(temp->argv[0]);
	else
		path = get_cmd_path(temp->argv[0], *env);
	if (!path)
	{
		if (temp->argv && temp->argv[0])
		{
			write(2, temp->argv[0], ft_strlen(temp->argv[0]));
			write(2, ": command not found\n", 21);
		}
		free(pipes);
		exit(127);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		printf("%s: Permission denied\n", path);
		free(path);
		free(pipes);
		exit(126);
	}
	envp = env_to_envp(*env);
	execve(path, temp->argv, envp);
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
		}
		else if (pid < 0)
		{
			perror("fork failed");
			exit(1);
		}
		temp = temp->next;
		i++;
	}
	close_pipe_and_wait(nb_cmds , nb_pipes , pipes);
}
