/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:53:04 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/02 18:53:04 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	f_main(t_cmd *cmd, t_env **env);
t_env	*create_env(char **envp);
void	free_t_env(t_env *env);

// utils2
t_cmd	*cmd_getter(int action, t_cmd *_cmd);
void	cleaning_cmd_and_pipes(int *pipes, t_env **env);
void	check_file(t_cmd *temp, char *path, t_env **env, int *pipes);