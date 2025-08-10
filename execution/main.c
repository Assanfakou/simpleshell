/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:00 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/10 01:08:51 by rmaanane         ###   ########.fr       */
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
		exit = do_unset(cmd->argv, env);
	return (exit);
}

void	executor(t_cmd *cmd, t_env **env)
{
	if (!cmd)
		return ;
	if (!cmd->argv || !cmd->argv[0])
		if (handle_redirect_only(cmd))
			return ;
	if (is_builtin(cmd) && !has_pipe(cmd))
		if (handle_builtin(cmd, env))
			return ;
	pipe_executor(cmd, env);
}

void	f_main(t_cmd *cmd, t_env **env, char *input)
{
	free(input);
	cmd_getter(SET, cmd);
	executor(cmd, env);
	free_t_cmd(cmd);
}
