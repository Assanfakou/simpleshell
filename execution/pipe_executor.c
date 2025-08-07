/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:24:56 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/06 22:25:46 by rmaanane         ###   ########.fr       */
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
}

void handle_fork_failed(t_cmd *temp, t_env **env)
{
	perror("fork failed");
	free_t_cmd(temp);
	free_t_env(*env);
	exit(1);
}
pid_t	handle_fork_and_execution(t_cmd *cmd, t_env **env, int *pipes, int nb_pipes)
{
	t_cmd	*temp;
	pid_t	pid;
	int		i;
	
	temp = cmd;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (temp)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			handle_child_process(temp, i, pipes, nb_pipes);
			handle_child_helper(temp, pipes, env);
			free_t_cmd(cmd);
		}
		else if (pid < 0)
			handle_fork_failed(temp, env);
		if (!temp->next )
			return (pid);
		temp = temp->next;
		
		i++;
	}
	return (0);
}


void	pipe_executor(t_cmd *cmd, t_env **env)
{
	int	nb_cmds;
	int	nb_pipes;
	int	*pipes;
	pid_t last_pid;

	setup_signals_and_pipes(cmd, &nb_cmds, &nb_pipes, &pipes);
	last_pid = handle_fork_and_execution(cmd, env, pipes, nb_pipes);
	close_pipe_and_wait(nb_cmds, nb_pipes, pipes, last_pid);
}

