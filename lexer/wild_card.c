#include "parce.h"

char	*ft_strstr(char *str, char *little, size_t z)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return (str);
	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (little && str[i + j] == little[j] && j < z)
			j++;
		if (j == z)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

bool	ends_with_substr(char *str, char *end, size_t i)
{
	if (ft_strlen(str) < i)
		return (false);
	while (str && *str)
		str++;
	str--;
	while (i > 0)
	{
		i--;
		if (*str != end[i])
			return (false);
		str--;
	}
	return (true);
}

bool	_wildcmp_help(char *str, char *pattern)
{
	size_t	sz;

	while (*pattern)
	{
		while (*pattern == '*')
		{
			if (!*(++pattern))
				return (true);
		}
		sz = 0;
		while (pattern[sz] != '*' && pattern[sz])
			sz++;
		if (sz > 0 && !pattern[sz])
			return (ends_with_substr(str, pattern, sz));
		str = ft_strstr(str, pattern, sz);
		if (!str)
			return (false);
		pattern += sz;
		str += sz;
	}
	return (true);
}

bool	wildcmp(char *str, char *pattern)
{
	while (*pattern && *pattern != '*')
	{
		if (*str != *pattern)
			return (false);
		str++;
		pattern++;
	}
	if (!*pattern && *str)
		return (false);
	if (!*pattern && !*str)
		return (true);
	return (_wildcmp_help(str, pattern));
}

void	join_current_dir(t_cmd *cmd, char *patern)
{
	DIR *dir_files;
	struct dirent *dir;
	
	dir_files = opendir(".");
	while (dir_files)
	{
		dir = readdir(dir_files);
		if (!dir)
			break;
			//printf("%s\n", dir->d_name);
		if (wildcmp(dir->d_name, patern))
			add_to_argv(cmd, ft_strdup(dir->d_name));
	}
	closedir(dir_files);
}
