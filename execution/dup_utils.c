/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:52:40 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/09 22:55:56 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_fd(int fd, t_redir *redir)
{
	if (fd < 0)
	{
		write(2, "minishell: ", 12);
		perror(redir->filename);
		return (1);
	}
	return (0);
}

void	dup_fd_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	dup_fd_inp(int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		exit(1);
	}
	close(fd);
}

int	safe_dup(int oldfd)
{
	int		newfd;

	newfd = dup(oldfd);
	if (newfd == -1)
	{
		perror("safe_dup failed");
		exit(EXIT_FAILURE);
	}
	return (newfd);
}
