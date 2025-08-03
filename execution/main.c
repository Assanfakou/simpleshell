/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:00 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/03 15:55:32 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	return (0);
}
int	exec_builtin(t_cmd *cmd, t_env **env)
{
	int	exit;

	exit = 0;
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		exit = do_cd(cmd->argv, *env);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		exit = do_echo(cmd->argv, *env);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		exit = do_pwd(cmd->argv, *env);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		exit = do_exit(cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		exit = do_env(cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		exit = do_export(cmd->argv, env);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		exit = do_unset(cmd->argv, *env);
	return (exit);
}

void	executor(t_cmd *cmd, t_env **env)
{
	if (!cmd)
		return ;
	if (!cmd->argv || !cmd->argv[0])
		if (handle_redirect_only(cmd))
			return ;

	skip_empty_cmd(cmd);

	if (is_builtin(cmd) && !has_pipe(cmd))
		if (handle_builtin(cmd, env))
			return ;
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		write(2, "Command '' not found\n", 22);
		status_set(127);
		return ;
	}
	pipe_executor(cmd, env);
}


void	f_main(t_cmd *cmd, t_env **env)
{
	executor(cmd, env);
	free_t_cmd(cmd);
}
