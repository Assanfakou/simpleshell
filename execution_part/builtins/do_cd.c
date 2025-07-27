/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:33 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/27 17:12:52 by rmaanane         ###   ########.fr       */
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

int check_path(char *path)
{
	if (!path)
		return (1);
	return (0);
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
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		printf("%s\n", path);
		return (1);
	}	
	return (0);
}
