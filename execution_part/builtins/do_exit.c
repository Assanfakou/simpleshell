/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:57 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/30 18:39:11 by rmaanane         ###   ########.fr       */
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

int	do_exit(char **args)
{
	int	n;

	printf("exit\n");
	if (!args[1])
		exit(status_get());
	if (!ft_isnumeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
		return (status_get());
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		status_set(1);
		return (status_get());
	}
	n = ft_atoi(args[1]);
	exit((unsigned char)n);
	
	return (0);
}
