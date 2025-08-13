#include "parce.h"

int asterisk_in_filename(char *target, t_cmd *cmd, t_token *tok)
{
	char *ast_tar;

	ast_tar = join_current_dir_redi(target);
	if (ast_tar)
		add_redirection(cmd, type_redir(tok), ast_tar);
	else
	{
		g_herdoc_stop = true;
		write (2, "wild_card error\n", 16);
	}
	return (1);
}

char *get_single_file_or_null(char *patern)
{
	DIR				*dir_files;
	struct dirent	*dir;
	char *filename;
	
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
	char *new_target;

	new_target = get_single_file_or_null(patern);
	free(patern);
	return (new_target);
}
