#include "parce.h"

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

char *herdoc_handler(t_env *env, t_lexer *lexer)
{
    bool expand;
    char *del;
    char *result;
    char *line;

    expand = false;
    del = join_herdok_del(lexer, &expand);
    result = ft_strdup("");
    signal(SIGINT, ft_sigint_handler_herdoc);
    while (!g_herdoc_stop)
    {
        line = readline("> ");
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
    return (NULL);
}

void redirect_del(t_token *tok, t_cmd *cmd, t_lexer *lexer, t_env *env)
{
    char *final_del;

	*tok = lexer_next_token(lexer);
	g_herdoc_stop = false;
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
	{
		*tok = lexer_next_token(lexer);
		add_redirection(cmd, type_redir(tok), collect_joined_words(lexer, env));
	}
}
