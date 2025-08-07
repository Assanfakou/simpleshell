/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:58:52 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/06 23:16:40 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "main.h"
#include <dirent.h>
#include <errno.h>

t_cmd *cmd_getter(int action, t_cmd *_cmd)
{
	static t_cmd *cmd; 

	if (action == GET)
		return cmd;
	if (action == SET)
		cmd = _cmd;
	return cmd;
}

void cleaning_cmd_and_pipes(int *pipes, t_env **env)
{
	free(pipes);
	free_t_cmd(cmd_getter(GET, NULL));
	free_t_env(*env);
}

int is_directory(char *path)
{
	DIR *dir;
	
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return 1;
	}
	else if (errno == ENOTDIR)
		return 0;
	else
		return 0;
}

void check_file(t_cmd *temp, char *path, t_env **env, int *pipes)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, temp->argv[0], ft_strlen(temp->argv[0]));
		write(2, ": Permission denied\n", 20);
		free(path);
		cleaning_cmd_and_pipes(pipes, env);
		exit(126);
	}
	if (is_directory(path))
	{
		write(2, "minishell: ", 11);
		write(2, temp->argv[0], ft_strlen(temp->argv[0]));
		write(2, ": Is a directory\n", 17);
		free(path);
		cleaning_cmd_and_pipes(pipes, env);
		exit(126);
	}
}