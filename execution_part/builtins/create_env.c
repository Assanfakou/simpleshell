#include "builtins.h"

t_env *create_env(char **envp)
{
    t_env *env = NULL;
    int i = 0;
    int j;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        if (envp[i][j] == '=')
        {
            t_env *new = malloc(sizeof(t_env));
            if (!new)
                return (NULL);
            
            new->name_of_variable = ft_substr(envp[i], 0, j);
            new->value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
            new->next = NULL;
            if (!env)
                env = new;
            else
            {
                t_env *tmp = env;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = new;
            }
        }
        i++;
    }
    return (env);
}