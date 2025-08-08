/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:23:02 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/06 13:23:04 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

void	ft_red_printf(t_redir_type type, char *name)
{
	if (type == R_HERDOC)
		printf("R_HERDOC {%s}\n", name);
	else if (type == R_OUTPUT)
		printf("R_OUTPUT {%s}\n", name);
	else if (type == R_INPUT)
		printf("R_INPUT {%s}\n", name);
	else if (type == R_APPAND)
		printf("R_APPAND {%s}\n", name);
}
/*
void	print_cmd(t_cmd *cmd)
{
	t_cmd	*walk;
	int		i;
	t_redir	*walk_redirect;

	walk = cmd;
	printf("-------------------\n");
	while (walk)
	{
		i = 0;
		if (walk->argv)
		{
			while (walk->argv[i])
			{
				printf("%s\n", walk->argv[i]);
				i++;
			}
		}
		walk_redirect = walk->redir;
		while (walk_redirect)
		{
			ft_red_printf(walk_redirect->type, walk_redirect->filename);
			walk_redirect = walk_redirect->next;
		}
		walk = walk->next;
		if (walk)
			printf("\n  --- PIPE -------------------\n\n");
	}
	printf("-------------------\n");
}
*/
