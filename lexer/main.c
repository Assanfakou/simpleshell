/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/30 17:08:17 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

int	g_exit_status = 0;

int	main(void)
{
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
				print_cmd(head);
			free_t_cmd(head);
		}
		free(input);
	}
}
