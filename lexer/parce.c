
#include "lexer.h"

int is_start_char(int c) 
{ 
    return ft_isalpha(c) || c == '_'; 
}

int is_var_char(int c)   
{ 
    return ft_isalnum(c) || c == '_'; 
}

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
				result = ft_itoa(3);
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
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE && next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
       	return (word);
}
/*
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
	t_redir *redir;
	int i;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * 12);
	while (tok->type && tok->type != TOK_PIPE)
	{
		i = 0;
		if ((tok->type == TOK_WORD || tok->type == TOK_DOUBLE || TOK_SINGLE) && i < 12) 
		{
			argv[i] == words_if_nospace(token, lexer);
			i++;
		}
	}
}*/

t_cmd *create_cmd(void)
{
	t_cmd *cmd;
       
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return cmd;
}

void add_to_argv(t_cmd *cmd, char *arg)
{
	int count = 0;
	char **new_argv;
	int i;

	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = arg;
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
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

void print_cmd(t_cmd *cmd)
{
	t_cmd *walk = cmd;
	
	while (walk)
	{
		printf("BETWEEN PIPE\n");
		int i = 0;
		while (walk->argv[i])
		{
			printf("%s\n", walk->argv[i]);
			i++;
		}
		while (walk->redir)
		{
			printf("type [%u] | file name : %s\n", walk->redir->type, walk->redir->filename);
			walk->redir = walk->redir->next;
		}
		walk = walk->next;
	}
}
void free_t_cmd(t_cmd *cmd)
{
	int i;	

	while (cmd)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		while (cmd->redir)
		{
			free(cmd->redir->filename);
			cmd->redir = cmd->redir->next;
		}
		cmd = cmd->next;
	}
}
