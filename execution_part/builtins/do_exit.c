#include "builtins.h"


int ft_isnumeric(char *str)
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

void	do_exit(char **args, int *exit_status)
{
	printf("exit\n");
	
	if (!args[1])
		exit(*exit_status);
	
	if (!ft_isnumeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		*exit_status = EXIT_FAILURE; //deja kaykon fstdlib dakchi 3lach ma7tajinach lih define
		return;
	}

	int n;
	n = ft_atoi(args[1]);
	exit((unsigned char)n);
}
