#include "parce.h"

int write_herr(void)
{
	write(2, "minishell: readline got NULL\n", 29);
	return (1);
}
/**
 ** join_herdok_del - Build the heredoc delimiter from lexer tokens.
 ** @lexer:  Data structure dat holds the line.
 ** @expand: param; set to true if delimiter contains quotes
 **          (meaning lines should NOT be expanded later).
 **
 ** Concatenates consecutive TOK_WORD/TOK_SINGLE/TOK_DOUBLE until a token
 ** with space==true or a different type is found. Advances the lexer.
 **
 ** Return: Allocated delimiter string on success.
 */

char	*join_herdok_del(t_lexer *lexer, bool *expand)
{
	char	*word;
	char	*processed;
	t_token	next_tok;
	t_token	tok;

	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		if (tok.type == TOK_SINGLE || tok.type == TOK_DOUBLE)
			*expand = true;	
		processed = ft_strndup(tok.literal, tok.len);
		word = join_and_free_two(word, processed);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}

/**
 ** expand_herdoc_line - Process one heredoc input line.
 ** @str: Line read from input (may be freed inside).
 ** @env: Environment for variable expansion.
 ** @expand: If true, do NOT expand variables; if false, expand $vars.
 **
 ** Appends a trailing '\n' to the processed line.
 **
 ** Return: Allocated "line+\n" on success.
 */

char	*expand_herdoc_line(char *str, t_env *env, bool expand)
{
	char	*word;
	char	*processed;

	word = ft_strdup("");
	if (ft_strchr(str, '$') && expand == false)
	{
		processed = expand_variable(str, env);
		free(str);
	}
	else
		processed = str;
	word = join_and_free_two(word, processed);
	processed = join_char('\n', word);
	return (processed);
}

/**
 ** herdoc_handler - Read a heredoc until its delimiter.
 ** @env: Environment for variable expansion.
 ** @lexer: Active lexer (used to parse the delimiter).
 **
 ** Builds the delimiter via join_herdok_del(), sets SIGINT handler, then
 ** reads lines with readline("> "). If the delimiter was quoted, variables
 ** are not expanded; otherwise they are expanded. Uses g_herdoc_stop to
 ** detect interruption.
 **
 ** Return: Allocated buffer containing the full heredoc on success, or NULL
 **         if interrupted.
 */

char *herdoc_handler(t_env *env, t_lexer *lexer)
{
	bool expand;
	
	char (*line), (*del), (*result);
	expand = false;
	del = join_herdok_del(lexer, &expand);
	result = ft_strdup("");
	signal(SIGINT, ft_sigint_handler_herdoc);
	while (!g_herdoc_stop)
	{
		line = readline("> ");
		if (!line)
			if (write_herr())
				break;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			free(del);
			break;
		}
		result = join_and_free_two(result, expand_herdoc_line(line , env, expand));
	}
	if (!g_herdoc_stop)
		return (result);
	free(result);
	return (NULL);
}

void redirect_del(t_token *tok, t_cmd *cmd, t_lexer *lexer, t_env *env)
{
    char *final_del;

	*tok = lexer_next_token(lexer);
	if (tok->type == TOK_HERDOC)
	{
		*tok = lexer_peek_next_token(lexer);
		final_del = herdoc_handler(env, lexer);
		if (final_del)
			add_redirection(cmd, type_redir(tok), final_del);
		else
			return ;
	}
	else
		add_redirection(cmd, type_redir(tok), collect_joined_words(lexer, env));
}
