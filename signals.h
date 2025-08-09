/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:52:38 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/08 16:54:32 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <unistd.h>

extern bool	g_herdoc_stop;

void		sigint_prompt(int sig);
void		ft_sigint_handler_herdoc(int signal);
void		handle_signals_interactive(void);

#endif