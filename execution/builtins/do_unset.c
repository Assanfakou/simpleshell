/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:36:47 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/09 22:51:31 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*remove_node(t_env *env, char *key)
{
	t_env	*next;

	if (!env)
		return (NULL);
	next = env->next;
	if (ft_strcmp(env->name_of_variable, key) == 0)
	{
		free(env->name_of_variable);
		free(env->value);
		free(env);
		return (next);
	}
	env->next = remove_node(env->next, key);
	return (env);
}

int	do_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		*env = remove_node(*env, args[i]);
		i++;
	}
	return (0);
}
