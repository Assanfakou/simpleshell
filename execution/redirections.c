/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:25 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/05 18:07:52 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int handle_input(t_redir *redir)  // fach kandiro wc < main.c matalan rah hna kanchdo stdin kanbdloh bfd dyala main.c bach y9ra mno sf!!!!!!!!
{
	int fd = open(redir->filename, O_RDONLY);
	if (check_fd(fd, redir))
		return (1);
	dup_fd_inp(fd);
	return (0);
}

int handle_output(t_redir *redir)
{
	int fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644); // trunc kat7iyd dakchi l9dim okatkteb jdid
	if (check_fd(fd, redir))
		return (1);
	dup_fd_out(fd);
	return (0);
}

int handle_append(t_redir *redir)
{
	int fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (check_fd(fd, redir))
		return (1);
	dup_fd_out(fd);
	return (0);
}

void handle_heardoc(char *delemeter)
{
	int fd;
	char *filename;
	int read_fd;

	read_fd = open("/dev/random", O_RDONLY, 0642);
	if (read_fd < 0)
		return ;
	filename = malloc(8);
	if (read(read_fd, filename, 8) == -1)
	{
		free(filename);
		return ;
	}
	close(read_fd);
	fd = open(filename, O_WRONLY | O_CREAT, 0642);
	if (fd < 0)
	{
		free(filename);
		return;
	}
	write(fd, delemeter, ft_strlen(delemeter));
	close(fd);
	fd = open(filename, O_RDONLY, 0642);
	if (fd < 0)
	{
		free(filename);
		return;
	}
	dup_fd_inp(fd);
	unlink(filename);
	free(filename);
}

int	find_redirection(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == R_INPUT)
		{
			if (handle_input(redir))
				return (1);
		}
		else if (redir->type == R_OUTPUT)
		{
			if (handle_output(redir))
				return (1);
		}
		else if (redir->type == R_APPAND)
		{
			if (handle_append(redir))
				return (1);
		}
		else if (redir->type == R_HERDOC)
			handle_heardoc(redir->filename);
		redir = redir->next;
	}
	return (0);
}
