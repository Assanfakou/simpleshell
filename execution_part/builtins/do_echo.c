#include "builtins.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

int do_echo(char **args, t_env *env)
{
    int i = 1;
    int new_line = 1;
    (void)env;
    while (args[i] && ft_strcmp(args[i] , "-n") == 0)
    {
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write (1, " ", 1);
        i++;
    }
    if (new_line)
        write (1, "\n", 1);
    return (0);
}