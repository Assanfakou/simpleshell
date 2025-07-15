#include "builtins.h"

int do_env(char **args, t_env **env)
{
    (void)args;
	t_env *walk = *env;

    while (walk)
    {
        if (walk)
            printf("%s=%s\n", walk->name_of_variable, walk->value);
        walk = walk->next;
    }
    return (0);
}
