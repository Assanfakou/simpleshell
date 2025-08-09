#include "execution.h"

int	read_dev_random(char **file)
{
	int	read_fd;

	read_fd = open("/dev/random", O_RDONLY, 0642);
	if (read_fd < 0)
		return (1);
	*file = malloc(8);
	if (read(read_fd, *file, 8) == -1)
	{
		free(*file);
		return (1);
	}
	close(read_fd);
	return (0);
}

void	handle_heardoc(char *delemeter)
{
	int		fd;
	char	*filename;

	if (read_dev_random(&filename))
		return ;
	fd = open(filename, O_WRONLY | O_CREAT, 0642);
	if (fd < 0)
	{
		free(filename);
		return ;
	}
	write(fd, delemeter, ft_strlen(delemeter));
	close(fd);
	fd = open(filename, O_RDONLY, 0642);
	if (fd < 0)
	{
		free(filename);
		return ;
	}
	dup_fd_inp(fd);
	unlink(filename);
	free(filename);
}
