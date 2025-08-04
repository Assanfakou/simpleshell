/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/04 17:19:40 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include "../execution/main.h"

char *_ft_getenv(char *name_of_variable, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->name_of_variable, name_of_variable) == 0)
            return (env->value);
        else
            env = env->next;
    }
    return (NULL);
}

int add_back_env(t_env **env, char **envp, int i, int j)
{
    t_env *new;
    t_env *tmp;

    new = malloc(sizeof(t_env));
    if (!new)
        return (1);
    new->value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
    new->name_of_variable = ft_substr(envp[i], 0, j);
    new->next = NULL;
    if (!*env)
        *env = new;
    else
    {
        tmp = *env;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (0);
}

t_env *_create_env(char **envp)
{
    t_env *env;
    int i;
    int j;

    env = NULL;
    i = 0;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        if (envp[i][j] == '=')
            if (add_back_env(&env, envp, i, j))
                return (NULL);
        i++;
    }
    return (env);
}

void free_t_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->name_of_variable);
        free(env->value);
        free(env);
        env = tmp;
    }
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_env	*env;
	t_lexer	lexer;
	char	*input;
	t_cmd	*head;

	head = NULL;
	env = _create_env(envp);
	while (1)
	{
        handle_signals_interactive();
		input = readline("minishell: ");
		if (!input)
		{
			write(1, "exit\n", 5);
			free(input);
			free_t_env(env);
			break ;
		}
		add_history(input);
		g_herdoc_stop = false;
		if (!find_error(lexer, input))
		{
			lexer = lexer_new(input);
			head = build_cmd_list(&lexer, env);
			if (!g_herdoc_stop && head)
			{
				free(input);
                cmd_getter(SET, head);
				f_main(head, &env);
				// print_ast(head);
			} 
			else
			{
				free(input);
				free_t_cmd(head);
			}
		}
	}
}
