#include "builtins.h"

void print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->name_of_variable, env->value);
        env = env->next;
    }
}
