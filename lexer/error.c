#include "lexer.h"

int check_errors(t_lexer *lexer ,t_token curr)
{
	t_token n_tok = lexer_peek_next_token(lexer); 

	if (curr.type == TOK_PIPE && n_tok.type == TOK_NULL)
	{
		print_error(curr.literal, curr.len);
		return (1);
	}
	else if (curr.type == TOK_HERDOC || curr.type == TOK_OUTPUT || curr.type == TOK_INPUT || curr.type == TOK_APPAND)
	{
		if (n_tok.type != TOK_WORD && n_tok.type != TOK_SINGLE && n_tok.type != TOK_DOUBLE)
		{
			print_error(n_tok.literal, n_tok.len);
			return (1);
		}
		else
			return (0);
	}
	else if (curr.type == TOK_PIPE && n_tok.type == TOK_PIPE)
	{
		print_error(n_tok.literal, n_tok.len);
		return (1);
	}
	return (0);
}

int check_first_tok(t_token *token)
{
	if (token->type == TOK_PIPE)
	{
		token->type = TOK_NULL;
		write(2, "minishell: syntax error near unexpeted token `|`", 49);
		write (2, "\n", 1);
		g_exit_status = 2;
		return (1);
	}
	else
		return (0);
}

int find_error(t_lexer lexer, char *input)
{
	t_token tok;
	
	lexer = lexer_new(input);	
	tok = lexer_next_token(&lexer);	
	printf("%s\n", input);
	if (check_first_tok(&tok))
		return (1);
	while (tok.type)
	{
		if (check_errors(&lexer ,tok) == 1)
			return (1);
		else if (tok.type == TOK_INVALID)
		{
			write (2, "UNMATCHED QUOTE\n", 17);
			return (1);
		}
		tok = lexer_next_token(&lexer);
	}
	return (0);	
}