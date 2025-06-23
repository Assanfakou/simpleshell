/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/23 12:32:33 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int g_exit_status = 0;





t_token token_new(char *s, t_token_type type, size_t len)
{
	t_token	tok;

	tok.literal = s;
	tok.type = type;
	tok.len = len;
	return (tok);
}

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else 
		return (0);
}

t_token token_word(t_lexer *lexer)
{
	t_token	tok;

	tok.literal = &lexer->input[lexer->pos];
	tok.len = 0;
	while (lexer->c && lexer->c != '|' && lexer->c != '<' 
			&& lexer->c != '>' && lexer->c != '\''
			&& lexer->c != '\"' && !ft_isspace(lexer->c))
	{
		tok.len++;
		read_char(lexer);
	}
	tok.type = TOK_WORD;
	return (tok);
}
	
bool skip_white_space(t_lexer *lexer)
{
	bool	found;

	found = 0;
	while (ft_isspace(lexer->c))
	{
		read_char(lexer);
		found = 1;
	}
	return (found);
}

t_token_type	toke_type(char c)
{
	if (c == '\'')
		return (TOK_SINGLE);
	else
		return (TOK_DOUBLE);
}
t_token token_s_d_word(t_lexer *lexer)
{
	t_token	tok;
	char	c;

	if (lexer->c == '\'')
		c = '\'';
	else
		c = '\"';	
	read_char(lexer);
	tok.literal = &lexer->input[lexer->pos];
	tok.len = 0;
	while (lexer->c && lexer->c != c)
	{
		tok.len++;
		read_char(lexer);
	}
	if (lexer->c == '\0')
	{
		tok.type = TOK_INVALID;
		return (tok);
	}
	read_char(lexer);
	tok.type = toke_type(c);
	return (tok);
}

t_token token_redir(t_lexer *lexer)
{
	t_token	tok;

	if (lexer->c == '<')
	{
		if (lexer->input[lexer->read_pos] == lexer->c)
		{
			tok = token_new(&lexer->input[lexer->pos], TOK_HERDOC, 2);
			read_char(lexer);
		}
		else
			tok = token_new(&lexer->input[lexer->pos], TOK_INPUT, 1);
	}
	else
	{
		if (lexer->input[lexer->read_pos] == lexer->c)
		{
			tok = token_new(&lexer->input[lexer->pos], TOK_APPAND, 2);
			read_char(lexer);
		}
		else
			tok = token_new(&lexer->input[lexer->pos], TOK_OUTPUT, 1);
	}
	read_char(lexer);
	return (tok);
}


t_token lexer_next_token(t_lexer *lexer)
{
	t_token	tok;
	bool	space;

	space = skip_white_space(lexer);
	if (lexer->c == '>' || lexer->c == '<')
		tok = token_redir(lexer);
	else if (lexer->c == '|')
	{
		tok = token_new(&lexer->input[lexer->pos], TOK_PIPE, 1);
		read_char(lexer);
	}
	else if (lexer->c == '\0')
		tok = token_new(NULL, TOK_NULL, 0);
	else if (lexer->c == '\'' || lexer->c == '\"')
		tok = token_s_d_word(lexer);
	else
		tok = token_word(lexer);
	tok.space = space;
	return (tok);
}

void print_error(char *pointer, size_t size)
{
	write (2, "minishell: syntax error near unexpeted token `", 47);
	write (2, pointer, size);
	write (2, "`\n", 2);
	g_exit_status = 2;
}

t_token lexer_peek_next_token(t_lexer *lexer)
{
	t_lexer	prev_lexer;
	t_token	tok;

	prev_lexer = *lexer;
	tok = lexer_next_token(lexer);
	*lexer = prev_lexer;
	return (tok);
}



int main()
{
	t_lexer	lexer;
	char	*input;
	t_cmd	*cmd = NULL;

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
