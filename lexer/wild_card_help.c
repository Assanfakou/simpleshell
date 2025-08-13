/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 06:51:27 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/13 07:06:01 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

void	asterisk_or_args(char *arg, t_cmd *cmd)
{
	if (arg && ft_strchr(arg, '*'))
	{
		if (!join_current_dir(cmd, arg))
			add_to_argv(cmd, arg);
		else
			free(arg);
	}
	else if (arg)
		add_to_argv(cmd, arg);
}

int	asterisk_in_filename(char *target, t_cmd *cmd, t_token *tok)
{
	char	*ast_tar;

	ast_tar = join_current_dir_redi(target);
	if (ast_tar)
		add_redirection(cmd, type_redir(tok), ast_tar);
	else
	{
		g_herdoc_stop = true;
		write(2, "wild_card error\n", 16);
	}
	return (1);
}

char	*get_single_file_or_null(char *patern)
{
	DIR				*dir_files;
	struct dirent	*dir;
	char			*filename;

	dir_files = opendir(".");
	filename = NULL;
	while (dir_files)
	{
		dir = readdir(dir_files);
		if (!dir)
			break ;
		if (dir->d_name[0] == '.' && patern[0] != '.')
			continue ;
		if (wildcmp(dir->d_name, patern))
		{
			if (filename)
				return (closedir(dir_files), NULL);
			filename = dir->d_name;
		}
	}
	if (filename)
		filename = ft_strjoin(filename, "");
	else
		filename = ft_strdup(patern);
	return (closedir(dir_files), filename);
}

char	*join_current_dir_redi(char *patern)
{
	char	*new_target;

	new_target = get_single_file_or_null(patern);
	free(patern);
	return (new_target);
}

bool	next_joined_word_is_pattern(t_lexer *lexer)
{
	t_token	next_tok;
	t_token	tok;
	t_lexer	lexer_back;
	size_t	i;

	lexer_back = *lexer;
	while (1)
	{
		tok = lexer_next_token(lexer);
		if (tok.type == TOK_SINGLE || tok.type == TOK_DOUBLE)
		{
			i = 0;
			while (i < tok.len)
			{
				if (tok.literal[i] == '*')
					return (*lexer = lexer_back, false);
				i++;
			}
		}
		next_tok = lexer_peek_next_token(lexer);
		if (wds(&tok) == 0 || next_tok.space == true)
			break ;
	}
	*lexer = lexer_back;
	return (true);
}
