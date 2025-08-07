/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:15:36 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/06 23:23:46 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../lexer/lexer.h"
# include "../lexer/parce.h"
# include "../libft/libft.h"
# include "builtins/builtins.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <sys/wait.h>

// utils
void	free_split_content(char **array);
char	*get_cmd_path(char *cmd, t_env *env);
char	**env_to_envp(t_env *env);
void	free_envp(char **envp);

// pipe_executor
void	pipe_executor(t_cmd *cmd, t_env **env);

// pipe_ex_helpers
int		count_cmds(t_cmd *cmd);
int		*create_pipes(t_cmd *cmd);
void	close_pipe_and_wait(int nb_cmds, int nb_pipes, int *pipes, pid_t last_pid);
int		has_output_redirection(t_cmd *cmd);

// pipe_ex_helpers2
void	handle_child_process(t_cmd *temp, int i, int *pipes, int nb_pipes);
void	handle_child_helper(t_cmd *temp, int *pipes, t_env **env);

// dup_utils
int		check_fd(int fd, t_redir *redir);
void	dup_fd_out(int fd);
void	dup_fd_inp(int fd);
int		safe_dup(int oldfd);

// redirection
int		find_redirection(t_redir *redir);

// main
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, t_env **env);

// main_helpers
int		has_pipe(t_cmd *cmd);
int		handle_redirect_only(t_cmd *cmd);
int		handle_builtin(t_cmd *cmd, t_env **env);

//herdoc

int read_dev_random(char **file);
void handle_heardoc(char *delemeter);

#endif
