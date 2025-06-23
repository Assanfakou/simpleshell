/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:08:19 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/23 16:12:01 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

char	*words_if_nospace(t_lexer *lexer)
{
	char *word, *if_var, *processed, *tmp;
	t_token next_tok, tok;
	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		if_var = ft_strndup(tok.literal, tok.len);
		if (tok.type == TOK_SINGLE || !ft_strchr(if_var, '$'))
			processed = if_var;
		else if (ft_strchr(if_var, '$'))
		{
			processed = expand_variable(if_var);
			free(if_var);
		}
		tmp = ft_strjoin(word, processed);
		free(word);
		free(processed);
		word = tmp;
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE && next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}

t_cmd	*build_cmd_list(t_lexer *lexer)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	tok;
	char	*merged;
	char	*target;

	head = create_cmd();
	cmd = head;
	while (1)
	{
		tok = lexer_peek_next_token(lexer);
		if (tok.type == TOK_WORD || tok.type == TOK_DOUBLE
			|| tok.type == TOK_SINGLE)
		{
			merged = words_if_nospace(lexer);
			add_to_argv(cmd, merged);
		}
		else if (tok.type == TOK_APPAND || tok.type == TOK_OUTPUT
			|| tok.type == TOK_INPUT || tok.type == TOK_HERDOC)
		{
			tok = lexer_next_token(lexer);
			target = words_if_nospace(lexer);
			add_redirection(cmd, type_redir(&tok), target);
		}
		else if (tok.type == TOK_PIPE)
		{
			cmd->next = create_cmd();
			cmd = cmd->next;
			tok = lexer_next_token(lexer);
		}
		else if (tok.type == TOK_NULL)
			break ;
	}
	return (head);
}
