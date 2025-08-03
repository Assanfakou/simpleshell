/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:11 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/02 18:53:11 by rmaanane         ###   ########.fr       */
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

	nb_cmd = count_cmds(cmd);
	nb_pipes = nb_cmd - 1;
	int *pipes = malloc(sizeof(int) * nb_pipes * 2); // 2 mean read and write
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&pipes[i * 2]) < 0) // pipe() → katsayb file descriptors-> Katkhlli lfd (file descriptors) f array omakadir walo
		{
			perror("pipe failed");
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_pipe_and_wait(int nb_cmds, int nb_pipes, int *pipes)
{
	int	i;
	int	j;
	int	status;

	// parent: close pipes
	i = 0;
	while (i < nb_pipes * 2)
		close(pipes[i++]);
	j = 0;
	while (j < nb_cmds)
	{
		wait(&status);
		if (WIFEXITED(status)) // hadi macro f C,katcheck wach dak child tsala normal (b exit(x)), mashi b signal (kill, segfault...).
			status_set(WEXITSTATUS(status)); // ila hya true, n9adro njibo exit status dyal command.
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