/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:07:44 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/07 22:27:23 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/main.h"
#include "parce.h"

int	free_exit(char *input, t_env *env)
{
	write(1, "exit\n", 5);
	free(input);
	free_t_env(env);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_lexer	lexer;
	char	*input;
	t_cmd	*head;

	(void)ac;
	(void)av;
	head = NULL;
	env = _create_env(envp);
	while (1)
	{
		handle_signals_interactive();
		input = readline("minishell: ");
		if (!input)
			if (free_exit(input, env))
				break ;
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
			}
			else
			{
				free(input);
				free_t_cmd(head);
			}
		}
		else
			free(input);
	}
}
