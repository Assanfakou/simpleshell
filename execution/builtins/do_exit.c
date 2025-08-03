/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:57 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/03 17:54:49 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include "builtins.h"

int	ft_isnumeric(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	cleaning_env_and_cmd(t_env **env)
{
	free_t_cmd(cmd_getter(GET, NULL));
	free_t_env(*env);
}

int	do_exit(char **args, t_env **env)
{
	int	n;

	write(2, "exit\n", 5);
	if (!args[1])
	{
		cleaning_env_and_cmd(env);
		exit(status_get());
	}
	if (!ft_isnumeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		cleaning_env_and_cmd(env);
		exit(2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		status_set(1);
	}
	n = ft_atoi(args[1]);
	cleaning_env_and_cmd(env);
	exit((unsigned char)n);
	return (0);
}
