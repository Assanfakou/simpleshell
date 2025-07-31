/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/31 12:03:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include "../execution_part/execution/main.h"

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

t_env *_create_env(char **envp)
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
	signal(SIGINT, sigint_prompt); // ctr + C
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
		{
			write(1, "exit\n", 5);
			free(input);
            free_t_env(env);
			break ;
		}
		add_history(input);
		if (!find_error(lexer, input))
		{
			lexer = lexer_new(input);
			head = build_cmd_list(&lexer, env);
			if (head)
            {
                free(input);
                f_main(head, envp, &env);
                // print_ast(head);
            } 
		}
	}
}
