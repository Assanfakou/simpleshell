/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:25 by rmaanane          #+#    #+#             */      
/*   Updated: 2025/08/05 18:30:45 by hfakou           ###   ########.fr       */
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
