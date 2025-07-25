/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:33 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/25 18:45:08 by rmaanane         ###   ########.fr       */
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

int	do_cd(char **args, t_env *env)
{
	char	*path;

	if (!args[1])
		path = ft_getenv("HOME", env);
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
