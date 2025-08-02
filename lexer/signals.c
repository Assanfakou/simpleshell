#include "signals.h"

bool	g_herdoc_stop = false;

void	ft_sigint_handler_herdoc(int signal)
{
	(void) signal;
	g_herdoc_stop = true;
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
	//free t_env
}
void handle_signals_interactive(void)
{
    signal(SIGINT, sigint_prompt);    // ctrl-C
    signal(SIGQUIT, SIG_IGN);         // ctrl-\ → does nothing.
}

