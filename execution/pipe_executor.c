/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:24:56 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/04 21:28:41 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"
#include "../signals.h"


void	setup_signals_and_pipes(t_cmd *cmd, int *nb_cmds, int *nb_pipes, int **pipes)
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_fork_and_execution(t_cmd *cmd, t_env **env, int *pipes, int nb_pipes)
{
	t_cmd	*temp = cmd;
	pid_t	pid;
	int		i = 0;

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
}

void	pipe_executor(t_cmd *cmd, t_env **env)
{
	int	nb_cmds;
	int	nb_pipes;
	int	*pipes;

	setup_signals_and_pipes(cmd, &nb_cmds, &nb_pipes, &pipes);
	handle_fork_and_execution(cmd, env, pipes, nb_pipes);
	close_pipe_and_wait(nb_cmds, nb_pipes, pipes);
}

