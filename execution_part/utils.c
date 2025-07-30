#include "execution/execution.h"

void free_split_content(char **array)
{
    int i;

    i = 0;
    while (array && array[i])
        free(array[i++]);
    free(array);
}

char *get_cmd_path(char *cmd, t_env *env)
{
    int i;
    char *chunk;
    char *full_path;
    char **paths;

    char *path_env = ft_getenv("PATH", env);
    if (!path_env || ft_strchr(cmd, '/')) //handle case ila 3titi ./minishell west minishell
        return (ft_strdup(cmd));

    paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;
    full_path = NULL;
    i = 0;
    while (paths && paths[i])
    {
        chunk = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(chunk, cmd);
        free(chunk);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        i++;
    }
    free_split_content(paths);
    return (full_path);
}

char *ft_strjoin_3(char *s1, char *s2, char *s3)
{
    char *tmp = ft_strjoin(s1, s2);
    char *result = ft_strjoin(tmp, s3);
    free(tmp);
    return result;
}

char **env_to_envp(t_env *env)
{
    int i = 0;
    char **envp;
    t_env *tmp = env;

    // Count
    int count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return NULL;

    tmp = env;
    while (tmp)
    {
        envp[i] = ft_strjoin_3(tmp->name_of_variable, "=", tmp->value); // you need to write ft_strjoin_3
        i++;
        tmp = tmp->next;
    }
    envp[i] = NULL;
    return envp;
}
