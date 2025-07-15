#include "builtins.h"
#define KRED  "\x1B[31m"

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
void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name_of_variable = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	print_export_list(t_env *env)
{
	while(env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name_of_variable, env->value);
		else
			printf("declare -x %s\n", env->name_of_variable);
		env = env->next;
	}
}

t_env	*find_new(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name_of_variable, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	update_or_add_env(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*do_exist;
	size_t	key_len;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		write(2, "bash: export: invalid argument\n", 32);
		return (1);
	}
	key_len = equal_sign - arg;
	key = ft_substr(arg, 0, key_len);
	if (!key)
		return (1);
	value = ft_strdup(equal_sign + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	do_exist = find_new(*env, key);
	if (do_exist)
	{
		free(do_exist->value);
		free(key);
		do_exist->value = value;
	}
	else
		env_add_back(env, env_new(key, value));
	return (0);
}

int	do_export(char **argv, t_env **env)
{
	int	i;

	if (!argv[1])
	{
		print_export_list(*env);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (update_or_add_env(argv[i], env))
			return (1);
		i++;
	}

	// print_env(*env);

	return (0);
}


// int _do_export(char **args, t_env **env)
// {
// 	int i = 1;
// 	int j;
// 	char *value;
// 	char *key;
// 	t_env *head = *env;
// /*
// 	printf("%s-----------------------------\n", KRED);
// 	print_env(head);
// 	printf("%s-----------------------------\n", KRED);
// */

// 	if (!args[1])
// 	{
// 		while (head)
// 		{
// 			if (head->value)
// 				printf("declare -x %s=\"%s\"\n", head->name_of_variable, head->value);
// 			else
// 				printf("declare -x %s\n", head->name_of_variable);
// 			head = head->next;
// 		}
// 		return 0;
// 	}

// 	while (args[i])
// 	{
// 		j = 0;
// 		while (args[i][j] && args[i][j] != '=')
// 			j++;

// 		if (args[i][j] == '=')
// 		{
// 			key = ft_substr(args[i], 0, j);
// 			value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);

// 			t_env *exist = name_already_exist(*env, key);
// 			exist->value = value;
// 			free(key); //7it katb9a anbdlo ghir value
// 		}
// 		else
// 		{
// 			t_env *new = malloc(sizeof(t_env));
// 			if (!new)
// 				return 1;

// 			new->name_of_variable = key;
// 			new->value = value;
// 			   printf("%s\n", new->value);
// 			new->next = NULL;

// 			t_env *tmp = *env;
// /*
// 			   print_env(*env);
// 			   printf("------------------------------------------------------------------------------");
// */
// 			while (tmp->next)
// 				tmp = tmp->next;
// 			tmp->next = new;
// 			/*
// 			   print_env(tmp);
// 			 */
// 		}
// 	}
// 	i++;

// 	return 0;
// }
