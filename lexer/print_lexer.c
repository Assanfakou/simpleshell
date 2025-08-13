/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:23:02 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/12 23:04:38 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

int	wds(t_token *tok)
{
	if (tok->type == TOK_WORD || tok->type == TOK_DOUBLE
		|| tok->type == TOK_SINGLE)
		return (1);
	return (0);
}

void	asterisk_or_args(char *arg, t_cmd *cmd)
{
	if (arg && ft_strchr(arg, '*'))
	{
		if (!join_current_dir(cmd, arg))
			add_to_argv(cmd, arg);
		else
			free(arg);
	}
	else if (arg)
		add_to_argv(cmd, arg);
}

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
