/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:24 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/25 18:11:17 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*parse_env_line(char *line)
{
	int		j;
	t_env	*new;

	j = 0;
	while (line[j] && line[j] != '=')
		j++;
	if (line[j] != '=')
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name_of_variable = ft_substr(line, 0, j);
	new->value = ft_substr(line, j + 1, ft_strlen(line) - j - 1);
	new->next = NULL;
	return (new);
}

t_env	*create_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	t_env	*tmp;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = parse_env_line(envp[i]);
		if (new)
		{
			if (!env)
				env = new;
			else
			{
				tmp = env;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new;
			}
		}
		i++;
	}
	return (env);
}
