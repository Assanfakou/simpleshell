/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:36:08 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/03 18:09:43 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export_loop(char **argv, t_env **env)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	while (argv[i])
	{
		if (!is_valid_format(argv[i]))
		{
			write(2, "minishell: export: `", 21);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "`: not a valid identifier\n", 27);
			flag = 0;
			i++;
			continue ;
		}
		if (handle_export_argument(argv[i], env))
			return (1);
		i++;
	}
	if (flag == 0)
		status_set(1);
	else
		status_set(0);
	return (status_get());
}

int	do_export(char **argv, t_env **env)
{
	if (!argv[1])
	{
		if (!*env)
			return (0);
		return (display_export(*env));
	}
	return (export_loop(argv, env));
}

