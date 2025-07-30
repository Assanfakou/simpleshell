#include <sys/ioctl.h>
#include <signal.h>
#include <readline/readline.h>
#include <stdbool.h>
# include <unistd.h> 

extern bool g_herdoc_stop;


void	sigint_prompt(int sig);
void	ft_sigint_handler_herdoc(int signal);

