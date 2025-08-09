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
#include "main.h"

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
void	handle_redirection_error(t_cmd *temp, int *pipes, t_env **env)
{
	if (!temp->next)
	{
		cleaning_cmd_and_pipes(pipes, env);
		exit(1);
	}
	else
	{
		cleaning_cmd_and_pipes(pipes, env);
		exit(0);
	}
}
void check_path_is_null(t_cmd *temp , char *path, t_env **env, int *pipes)
{
	if (!path)
	{
		if (temp->argv && temp->argv[0])
		{
			write(2, "minishell: ", 11);
			write(2, temp->argv[0], ft_strlen(temp->argv[0]));
			write(2, ": command not found\n", 21);
		}
		cleaning_cmd_and_pipes(pipes, env);
		exit(127);
	}
}

void	prepare_path_and_exec(t_cmd *temp, t_env **env, int *pipes)
{
	char	*path;
	char	**envp;

	if (temp->argv[0][0] == '/' || (temp->argv[0][0] == '.'
			&& temp->argv[0][1] == '/'))
		path = ft_strdup(temp->argv[0]);
	else
		path = get_cmd_path(temp->argv[0], *env);
	check_path_is_null(temp , path, env, pipes);
	check_file(temp, path, env, pipes);
	envp = env_to_envp(*env);
	if (execve(path, temp->argv, envp) == -1)
	{
		write(2, "minishell: ", 11);
		perror(temp->argv[0]);
		cleaning_cmd_and_pipes(pipes, env);
		free(path);
		free_envp(envp);
		exit(127);
	}
}
void	handle_child_helper(t_cmd *temp, int *pipes, t_env **env)
{
	if (find_redirection(temp->redir))
		handle_redirection_error(temp, pipes, env);
	if (is_builtin(temp))
	{
		if (ft_strcmp(temp->argv[0], "exit") == 0)
		{
			free(pipes);
			do_exit(temp->argv, env);
		}
		free(pipes);
		status_set(exec_builtin(temp, env));
		free_t_cmd(cmd_getter(GET, NULL));
		free_t_env(*env);
		exit(0);
	}
	prepare_path_and_exec(temp, env, pipes);
}

