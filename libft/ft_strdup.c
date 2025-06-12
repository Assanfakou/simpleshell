/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:12:05 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/12 12:32:04 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*buffer;
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	buffer = malloc(sizeof(char) * i + 1);
	if (buffer == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_strndup(const char *str, size_t size)
{
	char	*buffer;
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < size)
		i++;
	buffer = malloc(sizeof(char) * i + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (str[i] && i < size)
	{
		buffer[i] = str[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
