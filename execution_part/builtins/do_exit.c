/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:57 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/29 14:08:13 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	do_exit(char **args)
{
	int	n;

	printf("exit\n");
	if (!args[1])
		exit(g_exit_status);
	if (!ft_isnumeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_status = EXIT_FAILURE;// deja kaykon fstdlib dakchi 3lach ma7tajinach lih define
		return ;
	}
	n = ft_atoi(args[1]);
	exit((unsigned char)n);
}
