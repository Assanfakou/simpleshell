#include "lexer.h"

int is_start_char(int c) 
{ 
    return ft_isalpha(c) || c == '_'; 
}

int is_var_char(int c)   
{ 
    return ft_isalnum(c) || c == '_'; 
}

void	handle_env_var(char **res, char *var, size_t *i)
{
	size_t	j;
	char	*key;
	char	*val;
	char	*tmp;

	j = *i + 1;
	while (is_var_char(var[j]))
		j++;
	key = ft_substr(var, *i + 1, j - *i - 1);
	val = getenv(key);
	free(key);
	if (val)
	{
		tmp = ft_strjoin(*res, val);
		free(*res);
		*res = tmp;
	}
	*i = j;
}

char *ft_get_env(char *name, t_env *env)
{
	while (env)
	{
		if (env->name == name)
			return (env->content);
		else
			env = env->next;
	}
	return (NULL);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*expand_variable(char *var)
{
	size_t	i;
	char	*res;
	char	*tmp;
	char	t[2];

	i = 0;
	res = ft_strdup("");
	while (var[i])
	{
		if (var[i] == '$' && var[i + 1] == '?')
		{
			tmp = ft_itoa(2);
			res = join_and_free(res, tmp);
			free(tmp);
			i += 2;
		}
		else if (var[i] == '$' && is_start_char(var[i + 1]))
			handle_env_var(&res, var, &i);
		else
		{
			t[0] = var[i];
			t[1] = '\0';
			tmp = ft_strjoin(res, t);
			free(res);
			res = tmp;
			i++;
		}
	}
	return (res);
}

char *words_if_nospace(t_lexer *lexer)
{
	char *word;
	char *tmp;
	char *processed;
	char *if_var;
	t_token tok;
	t_token next_tok;
	
	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		if_var = ft_strndup(tok.literal, tok.len);
		processed = NULL;
		if (tok.type == TOK_SINGLE) 
			processed = if_var;
		else if (ft_strchr(if_var, '$'))
		{
			processed = expand_variable(if_var);
			free(if_var);
		}
		else
			processed = if_var;	
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

void add_redirection(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir *walk;
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return;
	redir->type = type;
	redir->filename = file;
	redir->next = NULL;
	if (!cmd->redir)
	{
		cmd->redir = redir;
		return;
	}
	walk = cmd->redir;
	while (walk->next)
		walk = walk->next;
	walk->next = redir;
}

t_cmd *build_cmd_list(t_lexer *lexer)
{
	t_cmd *head = create_cmd();
	t_cmd *cmd = head;
	t_token tok;
	t_token next;
	char *merged; 
	char *target;

	while (1)
	{
		tok = lexer_peek_next_token(lexer);
		if (tok.type == TOK_WORD || tok.type == TOK_DOUBLE || tok.type == TOK_SINGLE)
		{
			merged = words_if_nospace(lexer);
			add_to_argv(cmd, merged);
		}
		else if (tok.type == TOK_APPAND || tok.type == TOK_OUTPUT || tok.type == TOK_INPUT || tok.type == TOK_HERDOC)
		{
			tok = lexer_next_token(lexer);
			next = lexer_peek_next_token(lexer);
			if (next.type != TOK_WORD && next.type != TOK_DOUBLE && next.type != TOK_SINGLE)
			{
				printf("syntax error: expected file after redirection\n");
				return (NULL); 
			}
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
			break;
	}
	return head;
}

