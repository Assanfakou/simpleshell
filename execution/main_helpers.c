/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:52:53 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/02 18:52:53 by rmaanane         ###   ########.fr       */
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

void	skip_empty_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!cmd || !cmd->argv)
		return ;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0') 	// Free empty strings at the beginning
		free(cmd->argv[i++]);
	if (!cmd->argv[i])
	{
		free(cmd->argv);  // free the array itself
		cmd->argv = NULL; // daroriya bach n3rfo anaho rah khawi
		return ;
	}
	while (cmd->argv[i])
		cmd->argv[j++] = cmd->argv[i++]; // index i wasl valid command ,j ba9i f 0 7wlna valid command l 0
	cmd->argv[j] = NULL;
}

int	handle_redirect_only(t_cmd *cmd)
{
	int	saved_stdout;
	int save_stdinp;

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
	int	saved_stdout;
	int	redir_failed;

	saved_stdout = safe_dup(STDOUT_FILENO);
	redir_failed = find_redirection(cmd->redir);
	dup_fd_out(saved_stdout);
	close(saved_stdout);
	if (redir_failed)
	{
		status_set(1);
		return (1);
	}
	status_set(exec_builtin(cmd, env));
	return (1);
}