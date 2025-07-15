#include "builtins.h"

t_env *remove_node(t_env *env, char *key) // lghaya mn dik t_env treurni lista jdida fach tm7i
//odik env hiya head dyal list
{

    if (!env) // darori had check 3la hsab recusion la wslna lkher omal9a walo thbs
        return NULL;

    t_env *next = env->next;
    if (ft_strcmp(env->name_of_variable, key) == 0)
    {
         free(env->name_of_variable);
         free(env->value);
         free(env);

        // had l3ibat dlfree li 9bel maghaykhdmoch lamadrtich malloc fmain si non 7iydhom okhdem bstack aykhdem
        
        return (next); //kanrj3o dak next n7toh blast li tms7
    }
    env->next = remove_node(env->next, key); //ndozo lnext
    return (env); //rje3 liya head dyali
}


int *do_unset(char **args, t_env *env)
{
    int i = 1;

    
    while (args[i])
    {
        remove_node(env, args[i]);
        i++;
    }
    return (0);
}
