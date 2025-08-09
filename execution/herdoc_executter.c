/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_executter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:21:19 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/09 23:39:51 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_heardoc(char *delemeter)
{
	int		fd;
	char	*filename;

	filename = "42";
	fd = open(filename, O_WRONLY | O_CREAT, 0642);
	if (fd < 0)
		return ;
	write(fd, delemeter, ft_strlen(delemeter));
	close(fd);
	fd = open(filename, O_RDONLY, 0642);
	if (fd < 0)
		return ;
	dup_fd_inp(fd);
	unlink(filename);
}
