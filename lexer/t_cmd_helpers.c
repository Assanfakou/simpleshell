#include "lexer.h"

void add_to_argv(t_cmd *cmd, char *arg)
{
	int count;
	char **new_argv;
	int i;

	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
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

void print_cmd(t_cmd *cmd)
{
	t_cmd *walk = cmd;

	while (walk)
	{
		printf("BETWEEN PIPE\n");
		int i = 0;
		if (walk->argv)
		{
			while (walk->argv[i])
			{
				printf("%s\n", walk->argv[i]);
				i++;
			}
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
	t_cmd *walk;	
	t_redir *redir_tmp;

	while (cmd)
	{
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		while (cmd->redir)
		{
			free(cmd->redir->filename);
			redir_tmp = cmd->redir;
			cmd->redir = cmd->redir->next;
			free(redir_tmp);
		}
		walk = cmd;
		cmd = cmd->next;
		free(walk);
	}
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
