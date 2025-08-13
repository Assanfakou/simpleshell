/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:08:19 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/13 06:47:40 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include <stdbool.h>

char	*join_in_exp(t_token tok, char *if_var, t_env *env, char *word)
{
	char	*processed;
	char	*final;

	processed = NULL;
	if (tok.type == TOK_SINGLE || !ft_strchr(if_var, '$'))
		processed = if_var;
	else if (ft_strchr(if_var, '$'))
		processed = expand_variable(if_var, env);
	final = join_and_free_two(word, processed);
	return (final);
}

/*
 ** Collects and joins consecutive word-like tokens that are 
 **			not separated by spaces.
 ** Expands environment variables when appropriate,
 **				except inside single-quoted tokens.
 **
 ** @param lexer - pointer to the current lexer state
 ** @param env 		- the enviriment linked liste for expanding
 ** @return      - new allocated string representing the
 **			joined and processed word
 */

char	*collect_joined_words(t_lexer *lexer, t_env *env)
{
	char	*word;
	char	*if_var;
	t_token	next_tok;
	t_token	tok;
	bool	quoted;

	quoted = false;
	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		if (tok.type == TOK_SINGLE || tok.type == TOK_DOUBLE)
			quoted = true;
		if_var = ft_strndup(tok.literal, tok.len);
		word = join_in_exp(tok, if_var, env, word);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	if (quoted == false && ft_strlen(word) == 0)
		return (free(word), NULL);
	return (word);
}

int	check_for_red(t_token tok)
{
	if (tok.type == TOK_APPAND || tok.type == TOK_OUTPUT
		|| tok.type == TOK_INPUT || tok.type == TOK_HERDOC)
		return (1);
	return (0);
}

void	add_back_cmd(t_lexer *lexer, t_token *tok, t_cmd **cmd)
{
	t_cmd	*next;

	next = create_cmd();
	(*cmd)->next = next;
	*cmd = next;
	*tok = lexer_next_token(lexer);
}

/*
 ** Parses the input from the lexer and builds a linked list of commands.
 ** Handles command arguments, redirections (including heredocs), and pipes.
 **
 ** @param lexer - pointer to the lexer containing the token stream
 ** @return      - pointer to the head t_cmd list
 */

t_cmd	*build_cmd_list(t_lexer *lexer, t_env *env)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	tok;

	head = create_cmd();
	cmd = head;
	while (1)
	{
		tok = lexer_peek_next_token(lexer);
		if (wds(&tok))
		{
			if (next_joined_word_is_pattern(lexer))
				asterisk_or_args(collect_joined_words(lexer, env), cmd);
			else
				add_to_argv(cmd, collect_joined_words(lexer, env));
		}
		else if (check_for_red(tok))
			redirect_del(&tok, cmd, lexer, env);
		else if (tok.type == TOK_PIPE)
			add_back_cmd(lexer, &tok, &cmd);
		else if (tok.type == TOK_NULL)
			break ;
	}
	return (head);
}
