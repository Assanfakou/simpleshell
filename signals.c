/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:52:10 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/08 16:52:13 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "signals.h"

bool	g_herdoc_stop = false;

void	ft_sigint_handler_herdoc(int signal)
{
	(void)signal;
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
	status_set(130);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals_interactive(void)
{
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}
