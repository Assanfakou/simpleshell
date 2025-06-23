/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/23 15:27:34 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

int	g_exit_status = 0;

int	main(void)
{
	t_env	env;
	t_lexer	lexer;
	char	*input;
	t_cmd	*cmd;

	cmd = NULL;
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
			cmd = build_cmd_list(&lexer);
			print_cmd(cmd);
			free_t_cmd(cmd);
		}
		free(input);
	}
}
