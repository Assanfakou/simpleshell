/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/02 00:54:53 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include "../execution_part/execution/main.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_env	env;
	t_lexer	lexer;
	char	*input;
	t_cmd	*head;

	head = NULL;
	(void)env;
	while (1)
	{
		input = readline("JUST_TYPE #$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(input);
		if (!find_error(lexer, input))
		{
			lexer = lexer_new(input);
			head = build_cmd_list(&lexer);
			if (head)
				f_main(head, envp); 
		}
		free(input);
	}
}
