/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:48:03 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/02 18:48:03 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_child_process(t_cmd *temp, int i, int *pipes, int nb_pipes)
{
	int	j;

	if (i != 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (temp->next && !has_output_redirection(temp))
		dup2(pipes[i * 2 + 1], STDOUT_FILENO);
	j = 0;
	while (j < nb_pipes * 2)
		close(pipes[j++]);
}

void	handle_child_helper(t_cmd *temp, int *pipes, t_env **env)
{
	if (find_redirection(temp->redir))
		handle_redirection_error(temp);
	if (is_builtin(temp))
	{
		exec_builtin(temp, env);
		free(pipes);
		exit(0);
	}
	prepare_path_and_exec(temp, env, pipes);
}