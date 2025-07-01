#include "builtins.h"

int do_pwd(char **args, t_env *env)
{
    (void)args;
    (void)env;
    char *pwd;


    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (1);
    
    printf("%s\n", pwd);
    free(pwd);

    return (0);
}
