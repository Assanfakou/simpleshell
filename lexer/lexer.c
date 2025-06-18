/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/18 17:01:55 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int g_exit_status = 0;

void print_lexer(t_lexer *lexer)
{
	printf("Input: \"%s\"\n", lexer->input);
	printf("char: %c;%zu\n", lexer->c, lexer->pos);
	printf("Future index: %zu\n", lexer->read_pos);
}


void	read_char(t_lexer *lexer)
{
	if (lexer->input[lexer->read_pos] == '\0')
	{
		lexer->c = 0;
		return ;
	}
	else
		lexer->c = lexer->input[lexer->read_pos];
	lexer->pos = lexer->read_pos;
	lexer->read_pos++;
}

t_lexer lexer_new(char *str)
{
	t_lexer l;

	l.input = str;
	l.read_pos = 0;
	l.c = 0;
	l.pos = 0;
	l.len = strlen(str);
	read_char(&l);
	return (l);
}

t_token token_new(char *s, t_token_type type, size_t len)
{
	t_token tok;

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
	t_token tok;

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
	bool found;

	found = 0;
	while (ft_isspace(lexer->c))
	{
		read_char(lexer);
		found = 1;
	}
	return (found);
}

t_token token_s_d_word(t_lexer *lexer)
{
	t_token tok;
	char c;

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
	if (c == '\'')
		tok.type = TOK_SINGLE;
	else
		tok.type = TOK_DOUBLE;
	return (tok);
}

t_token token_redir(t_lexer *lexer)
{
	t_token tok;

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

void token_print(t_token token)
{
	if (token.type == TOK_INPUT)
		printf("(TOK_IN)");
	else if (token.type == TOK_HERDOC)
		printf("(TOK_HERDOC)");
	else if (token.type == TOK_OUTPUT)
		printf("(TOK_OUT)");
	else if (token.type == TOK_PIPE)
		printf("(TOK_PIPE)");
	else if (token.type == TOK_NULL)
		printf("(nil)");
	else if (token.type == TOK_WORD)
		printf("(TOK_WORD)");
	else if (token.type == TOK_SINGLE)
		printf("(TOK_SINGLE)");
	else if (token.type == TOK_DOUBLE)
		printf("(TOK_DOUBLE)");
	else if (token.type == TOK_APPAND)
		printf("(TOK_APPAND)");
	else if (token.type == TOK_INVALID)
		printf("(TOK_INVALID)");
	else
	{
		UNIMPLEMENTED("INVALID TOKEN RECEIVED");
	}
	printf(" \"%.*s\"\n", (int) token.len, token.literal);
}

t_token lexer_next_token(t_lexer *lexer)
{
	t_token tok;
	bool space;

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

void print_until_size(char *pointer, size_t size)
{
	write(1, "minishell: syntax error near unexpeted token ", 46);
	write (1, pointer, size);
	write (1, "\n", 1);
}

t_token lexer_peek_next_token(t_lexer *lexer)
{
	t_lexer prev_lexer;
	t_token tok;

	prev_lexer = *lexer;
	tok = lexer_next_token(lexer);
	*lexer = prev_lexer;
	return (tok);
}

int check_errors(t_lexer *lexer ,t_token curr)
{
	t_token n_tok = lexer_peek_next_token(lexer); 

	if (curr.type == TOK_PIPE && n_tok.type == TOK_NULL)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		g_exit_status = 2;
		return (1);
	}
	/*
	else if (curr.type == TOK_PIPE && (n_tok.type != TOK_WORD && n_tok.type != TOK_DOUBLE && n_tok.type != TOK_SINGLE))
	{
		print_until_size(n_tok.literal, n_tok.len); 
		g_exit_status = 2;
		return (1);
	}*/
	else if (curr.type == TOK_HERDOC || curr.type == TOK_OUTPUT || curr.type == TOK_INPUT || curr.type == TOK_APPAND)
	{
		if (n_tok.type != TOK_WORD && n_tok.type != TOK_SINGLE && n_tok.type != TOK_DOUBLE)
		{
			print_until_size(n_tok.literal, n_tok.len); 
			g_exit_status = 2;
			return (1);
		}
		else
			return (0);

	}
	else if (curr.type == TOK_PIPE && n_tok.type == TOK_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

int check_first_tok(t_token *token)
{
	if (token->type == TOK_PIPE)
	{
		token->type = TOK_NULL;
		write(2, "minishell: syntax error near unexpeted token |\n", 48);
		return (1);
	}
	else
		return (0);
}

int main()
{
	t_lexer lexer;
	t_token tok;
	char *input;
	t_cmd *cmd = NULL;
	int i = 0;

	while (1)
	{
		input = readline("JUST_TYPE #$ ");
		add_history(input);
		lexer = lexer_new(input);
		tok = lexer_next_token(&lexer);
		printf("%s\n", input);
		if (check_first_tok(&tok))
				i = 1;
		while (tok.type && !check_errors(&lexer, tok) && i == 0)
		{
			if (check_errors(&lexer ,tok) == 1)
				i = 1;
			tok = lexer_next_token(&lexer);
		}
		if (i == 0)
		{
			lexer = lexer_new(input);
			cmd = build_cmd_list(&lexer);
			print_cmd(cmd);
		}
	}
	
}
