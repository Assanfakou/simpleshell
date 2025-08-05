/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:33 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/05 12:04:07 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_getenv(char *name_of_variable, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name_of_variable, name_of_variable) == 0)
			return (env->value);
		else
			env = env->next;
	}
	return (NULL);
}

int	check_path(char *path)
{
	if (!path)
		return (1);
	return (0);
}

int	change_dir_and_check(char *path)
{
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		perror("");
		status_set(1);
		return (status_get());
	}
	return (status_get());
}

int	do_cd(char **args, t_env *env)
{
	char	*path;

	if (!args[1])
	{
		path = ft_getenv("HOME", env);
		if (check_path(path))
			return (printf("cd: HOME not set\n"), 1);
	}
	else if (args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		status_set(1);
		return (status_get());
	}
	else
		path = args[1];
	change_dir_and_check(path);
	return (status_get());
}
