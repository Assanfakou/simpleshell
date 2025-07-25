/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:36:47 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/25 19:45:19 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*remove_node(t_env *env, char *key)
{
	if (!env)// darori had check 3la hsab recusion la wslna lkher omal9a walo thbs
		return (NULL);

	t_env *next = env->next;
	if (ft_strcmp(env->name_of_variable, key) == 0)
	{
		free(env->name_of_variable);
		free(env->value);
		free(env);
		return (next); // kanrj3o dak next n7toh blast li tms7
	}
	env->next = remove_node(env->next, key); // ndozo lnext
	return (env);// rje3 liya head dyali
}

int	*do_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_node(env, args[i]);
		i++;
	}
	return (0);
}
