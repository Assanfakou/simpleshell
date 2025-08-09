/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:52:53 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/09 22:56:59 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	has_pipe(t_cmd *cmd)
{
	if (cmd && cmd->next != NULL)
		return (1);
	else
		return (0);
}

int	handle_redirect_only(t_cmd *cmd)
{
	int	saved_stdout;
	int	save_stdinp;

	saved_stdout = safe_dup(STDOUT_FILENO);
	save_stdinp = safe_dup(STDIN_FILENO);
	if (find_redirection(cmd->redir))
	{
		dup_fd_out(saved_stdout);
		dup_fd_inp(save_stdinp);
		status_set(1);
		return (1);
	}
	dup_fd_out(saved_stdout);
	dup_fd_inp(save_stdinp);
	status_set(0);
	return (1);
}

int	handle_builtin(t_cmd *cmd, t_env **env)
{
	int		saved_stdout;
	int		saved_input;

	saved_stdout = safe_dup(STDOUT_FILENO);
	saved_input = safe_dup(STDIN_FILENO);
	if (find_redirection(cmd->redir))
	{
		dup_fd_out(saved_stdout);
		dup_fd_inp(saved_input);
		status_set(1);
		return (1);
	}
	status_set(exec_builtin(cmd, env));
	dup_fd_out(saved_stdout);
	dup_fd_inp(saved_input);
	return (1);
}
