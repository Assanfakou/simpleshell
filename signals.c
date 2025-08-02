#include "signals.h"
#include "lexer/lexer.h"

bool	g_herdoc_stop = false;

void	ft_sigint_handler_herdoc(int signal)
{
	(void) signal;
	g_herdoc_stop = true;
	status_set(130);	
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	sigint_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

