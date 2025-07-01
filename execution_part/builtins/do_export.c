#include "builtins.h"

t_env *name_already_exist(t_env *env, char *name_of_variable)
{
    while (env)
    {
        if (ft_strcmp(name_of_variable, env->name_of_variable) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

int do_export(char **args, t_env *env)
{
    int i = 1;
    int j;

    if (!args[1])
    {
        while (env)
        {
            if (env->value)
                printf("declare -x %s=\"%s\"\n", env->name_of_variable, env->value);
            else
                printf("declare -x %s\n", env->name_of_variable);
            env = env->next;
        }
        return 0;
    }

    while (args[i])
    {
        j = 0;
        while (args[i][j] && args[i][j] != '=')
            j++;

        if (args[i][j] == '=')
        {
            char *key = ft_substr(args[i], 0, j);
            char *value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);

            t_env *exist = name_already_exist(env, key);
            if (exist)
            {
                free(exist->value);
                exist->value = value;
                free(key); //7it katb9a anbdlo ghir value
            }
            else
            {
                t_env *new = malloc(sizeof(t_env));
                if (!new)
                    return 1;

                new->name_of_variable = key;
                new->value = value;
                new->next = NULL;

                t_env *tmp = env;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = new;
            }
        }
        i++;
    }
    return 0;
}
