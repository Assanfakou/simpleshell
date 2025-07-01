#include "builtins.h"

int do_env(char **args, t_env *env)
{
    (void)args;

    while (env)
    {
        if (env->value)
            printf("%s=%s\n", env->name_of_variable, env->value);
        env = env->next;
    }
    return (0);
}
