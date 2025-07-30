/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:15:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/30 09:20:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

void	print_error(char *pointer, size_t size)
{
	write(2, "minishell: syntax error near unexpeted token `", 47);
	write(2, pointer, size);
	write(2, "'\n", 2);
	status_set(2);
}

void	print_newline_error(void)
{
	write(2, "minishell: syntax error near unexpeted token `", 47);
	write(2, "newline", 7);
	write(2, "`\n", 2);
	status_set(2);
}
/**
 ** check_errors - Validate token sequence for basic syntax errors.
 ** @lexer: Active lexer (used to peek the next token).
 ** @curr:  Current token already read/consumed.
 **
 ** Flags errors for:
 **  - '|' followed by end of input.
 **  - A redirection token without a following valid target.
 **  - '|' followed by another '|'.
 ** Prints an error (print_error/print_newline_error) when applicable.
 **
 ** Return: 1 if an error is detected, 0 otherwise.
 */

int	check_errors(t_lexer *lexer, t_token curr)
{
	t_token	n_tok;
	n_tok = lexer_peek_next_token(lexer);
	if (curr.type == TOK_PIPE && n_tok.type == TOK_NULL)
	{
		print_error(curr.literal, curr.len);
		return (1);
	}
	else if (check_for_red(curr))
	{
		if (n_tok.type == TOK_NULL)
		{
			print_newline_error();
			return (1);
		}
		else if (not_token(n_tok))
			return (1);
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

int	check_first_tok(t_token *token)
{
	if (token->type == TOK_PIPE)
	{
		token->type = TOK_NULL;
		write(2, "minishell: syntax error near unexpeted token `|`", 49);
		write(2, "\n", 1);
		status_set(2);
		return (1);
	}
	else
		return (0);
}
/**
 * find_error - Run lexical and syntax checks on the input line.
 * @lexer: Lexer value (reinitialized internally with @input).
 * @input: Command line to validate.
 *
 * Behavior:
 *  - Returns 1 for empty input.
 *  - Initializes a lexer from @input and checks the first token
 *    with check_first_tok().
 *  - Iterates tokens; if a TOK_INVALID is found, prints
 *    "UNMATCHED QUOTE\n" to stderr and sets status to 2.
 *  - Delegates sequence validation to check_errors().
 *
 * Side effects: writes to stderr; calls status_set(2) on unmatched quotes.
 *
 * Return: 1 if any error is detected; 0 if the input is syntactically valid.
 */

int	find_error(t_lexer lexer, char *input)
{
	t_token	tok;

	if (input[0] == '\0')
		return (1);
	lexer = lexer_new(input);
	tok = lexer_next_token(&lexer);
	if (check_first_tok(&tok))
		return (1);
	while (tok.type)
	{
		if (tok.type == TOK_INVALID)
		{
			write(2, "UNMATCHED QUOTE\n", 17);
			status_set(2);
			return (1);
		}
		else if (check_errors(&lexer, tok) == 1)
			return (1);
		tok = lexer_next_token(&lexer);
	}
	return (0);
}
