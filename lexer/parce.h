/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:34:33 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/01 12:01:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCE_H
# define PARCE_H

# include "lexer.h"
#include "../signals.h"

typedef enum s_redir_type
{
	R_HERDOC,
	R_OUTPUT,
	R_INPUT,
	R_APPAND,
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_env
{
	char *name_of_variable;
	char *value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char **argv;
	t_redir *redir;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				*build_cmd_list(t_lexer *lexer, t_env *env);
void				print_cmd(t_cmd *cmd);


void redirect_del(t_token *tok, t_cmd *cmd, t_lexer *lexer, t_env *env);
t_redir_type		type_redir(t_token *token);
void				free_t_cmd(t_cmd *cmd);
void				print_cmd(t_cmd *cmd);
t_cmd				*create_cmd(void);
void				add_to_argv(t_cmd *cmd, char *arg);
void				add_redirection(t_cmd *cmd, t_redir_type type, char *file);
int				check_for_red(t_token tok);

char				*expand_variable(char *var, t_env *env);
char				*join_and_free(char *s1, char *s2);
char				*join_and_free_two(char *s1, char *s2);
void				handle_env_var(char **res, char *var, size_t *i, t_env *env);
char				*parse_heredoc_delim(t_lexer *lexer, bool *expand);
char				*collect_joined_words(t_lexer *lexer, t_env *env);
char	*join_char(char c, char *res);

char *_ft_getenv(char *name_of_variable, t_env *env);

char *herdoc_handler(t_env *env, t_lexer *lexer);
char	*expand_herdoc_line(char *str, t_env *env, bool expand);
char	*join_herdok_del(t_lexer *lexer, bool *expand);

void print_ast(t_cmd *ast);


#endif
