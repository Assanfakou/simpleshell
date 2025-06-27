/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:08:19 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/27 22:51:01 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

char	*join_and_free_two(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*words_if_nospace(t_lexer *lexer)
{
	char	*word;
	char	*if_var;
	char	*processed;
	t_token	next_tok;
	t_token	tok;

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
		word = join_and_free_two(word, processed);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}

char	*herdoc_word(t_lexer *lexer, bool *expand)
{
	char	*word;
	char	*processed;
	t_token	next_tok;
	t_token	tok;

	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		processed = ft_strndup(tok.literal, tok.len);
		if (tok.type == TOK_DOUBLE)
			*expand = true;
		word = join_and_free_two(word, processed);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}

int	check_for_red(t_token tok)
{
	if (tok.type == TOK_APPAND || tok.type == TOK_OUTPUT
		|| tok.type == TOK_INPUT || tok.type == TOK_HERDOC)
		return (1);
	return (0);
}

t_cmd	*build_cmd_list(t_lexer *lexer)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	tok;
	bool expand;

	head = create_cmd();
	expand = false;
	cmd = head;
	while (1)
	{
		tok = lexer_peek_next_token(lexer);
		if (tok.type == TOK_WORD || tok.type == TOK_DOUBLE
			|| tok.type == TOK_SINGLE)
			add_to_argv(cmd, words_if_nospace(lexer));
		else if (check_for_red(tok))
		{
			if (tok.type == TOK_HERDOC)
			{
				tok = lexer_next_token(lexer);
				add_redirection(cmd, type_redir(&tok), herdoc_word(lexer, &expand), expand);
			}
			else
			{
				tok = lexer_next_token(lexer);
				add_redirection(cmd, type_redir(&tok), words_if_nospace(lexer), expand);
			}
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
