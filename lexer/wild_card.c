/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 07:08:53 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/13 07:09:18 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
** ends_with_substr:
** Checks if `str` ends with the string `end` of length `i`.
** Returns true if the suffix matches exactly, otherwise false.
*/

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

/*
** _wildcmp_help:
** Helper function for wildcmp(). Handles cases when `pattern`
** contains '*' wildcards. Matches each segment of the pattern
** against `str` in the correct order.
**
** Rules:
** - '*' can match any sequence (including empty).
** - If the last segment of the pattern has no trailing '*',
**   it must match the end of the string.
*/

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

/*
** wildcmp:
** Compares `str` with `pattern` where '*' matches any sequence of characters.
** Returns true if the string fully matches the pattern, false otherwise.
**
** Example:
**   wildcmp("hello.c", "*.c")  -> true
**   wildcmp("hello.c", "h*o.c") -> true
**   wildcmp("hello.c", "*.h")   -> false
*/

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
	return (_wildcmp_help(str, pattern));
}

/*
** join_current_dir:
** Opens the current directory (".") and iterates over each file.
** - Hidden files (starting with '.') are skipped unless the pattern
**   also starts with '.'.
** - Files matching the wildcard `patern` are duplicated and added
**   to the command arguments via add_to_argv().
**
** Frees `patern` before returning.
*/

bool	join_current_dir(t_cmd *cmd, char *patern)
{
	DIR				*dir_files;
	struct dirent	*dir;
	bool			added;

	dir_files = opendir(".");
	added = false;
	if (!dir_files)
	{
		write(2, "Error while opening the directory\n", 34);
		return (false);
	}
	while (dir_files)
	{
		dir = readdir(dir_files);
		if (!dir)
			break ;
		if (dir->d_name[0] == '.' && patern[0] != '.')
			continue ;
		if (wildcmp(dir->d_name, patern))
		{
			add_to_argv(cmd, ft_strdup(dir->d_name));
			added = true;
		}
	}
	return (closedir(dir_files), added);
}
