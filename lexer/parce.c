
#include "parce.h"

t_redir_type type_redir(t_token *token)
{
	if (token->type == TOK_HERDOC)
		return (R_HERDOC);
	else if (token->type == TOK_INPUT)
		return (R_INPUT);
	else if (token->type == TOK_OUTPUT)
		return (R_OUTPUT);
	else if (token->type == TOK_APPAND)
		return (R_APPAND);
	else
		return 0;
}
char *expand_variable(char *variable)
{
    int here;
    size_t len;
    char *result = ft_strdup("");
    size_t i;

        len = ft_strlen(variable);
        if (len >= 2)
		return (ft_strdup(variable));
        i = 0;
        while (variable[i])
        {
            if (variable[i] == '$')
            {
                if (variable[i + 1] == '?')
                {
                    result = ft_itoa(g_exit_status);
                    i += 2;
                }
                else if (is_start_char(variable[i + 1]))
                {
                    size_t j = i;
                    while (is_var_char(variable[j])) 
			    j++;
		    char *val = getenv(ft_substr(variable, i, j - i));
                    if (val)
                    {
                        size_t val_len = ft_strlen(val);
                        result = ft_calloc(val_len + 1, 1);
                        ft_memcpy(result, val, val_len);
                    }
                    i = j;
                }
            }
            else
	    {
		    char t[2] = { variable[i++], 0 };
		    char *tmp = ft_strjoin(result, t);
		    free(result);
		    result = tmp;
	    }
	}
	return (result);
}
char *words_if_nospace(t_token *tok, t_lexer *lexer, t_env *env)
{
	char *word;
	char *tmp;
	char *processed;
	char *if_var;
	
	word = ft_strdup("");
	while (tok->type == TOK_WORD || tok>type == TOK_SINGLE || tok->type == TOK_DOUBLE)
	{
		if_var = ft_strndup(tok->literal, tok->len);
		processed = NULL;
		if (tok.type == TOK_SINGLE)
			processed = if_var;
		else
		{
			if (ft_strchr(if_var, '$'))
			{
				processed = expand_variable(if_var);
				free(if_var);	
			}
			else
				processed = if_var;
		}
		tmp = ft_strjoin(word, processed);
		free(word);
		free(processed);
		word = tmp;
		if (tok->space == true)
			break;
		*tok = lexer_next_token(lexer);
		if (tok->type == TOK_NULL)
			break;
	}
	return (word);
}


t_redir *new_redir(t_token *tok, t_lexer *lexer)
{
	t_redir *redirect;
	t_token *next; 
	
	redirect = malloc(sizeof(t_redir));
	redirect->type = type_redir(tok);
	next = lexer_next_token(lexer); 
	redirect->filename = word_if_nospace(tok, lexer);
	redirect->next = NULL;
	return (redirect);	
}

t_cmd *new_cmnd(t_token *token, t_lexer *lexer)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	
	while (tok->type && tok->type != TOK_PIPE)
	{
		if (tok->type == TOK_WORD || tok
	}
}	
