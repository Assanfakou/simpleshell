/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:57 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/13 02:45:55 by rmaanane         ###   ########.fr       */
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
	int (n);
	if (!cmd_getter(GET, NULL)->next)
		write(2, "exit\n", 5);
	if (!args[1])
	{
		cleaning_env_and_cmd(env);
		exit(status_get());
	}
	if (!ft_isnumeric(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		cleaning_env_and_cmd(env);
		exit(2);
	}
	if (args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (status_set(1), 1);
	}
	n = ft_atoi(args[1]);
	cleaning_env_and_cmd(env);
	exit((unsigned char)n);
	return (0);
}
