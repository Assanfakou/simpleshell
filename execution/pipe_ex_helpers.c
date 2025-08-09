/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:11 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/09 23:06:57 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	*create_pipes(t_cmd *cmd)
{
	int	nb_cmd;
	int	nb_pipes;
	int	i;
	int	*pipes;

	nb_cmd = count_cmds(cmd);
	nb_pipes = nb_cmd - 1;
	pipes = malloc(sizeof(int) * nb_pipes * 2);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&pipes[i * 2]) < 0)
		{
			perror("pipe failed");
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	exit_with_signals(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
	else if (WTERMSIG(status) == SIGINT)
		ft_putendl_fd("", 2);
	status_set(128 + WTERMSIG(status));
}

void	close_pipe_and_wait(int nb_cmds, int nb_pipes, int *pipes,
		pid_t last_pid)
{
	pid_t	child_pid;

	int (i), (j), (status);
	i = 0;
	while (i < nb_pipes * 2)
		close(pipes[i++]);
	j = 0;
	while (j < nb_cmds)
	{
		child_pid = wait(&status);
		if (child_pid == last_pid)
		{
			if (WIFEXITED(status))
				status_set(WEXITSTATUS(status));
			else
				exit_with_signals(status);
		}
		j++;
	}
	free(pipes);
}

int	has_output_redirection(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == R_OUTPUT || r->type == R_APPAND)
			return (1);
		r = r->next;
	}
	return (0);
}
