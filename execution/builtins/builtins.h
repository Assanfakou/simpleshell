/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:11 by rmaanane          #+#    #+#             */
/*   Updated: 2025/08/03 18:09:08 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../lexer/lexer.h"
# include "../../lexer/parce.h"
# include "../../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// do_echo
int		do_echo(char **args, t_env *env);

// do_cd
char	*ft_getenv(char *name_of_variable, t_env *env);
int		do_cd(char **args, t_env *env);

// do_pwd
int		do_pwd(char **args, t_env *env);

// do_env
int		do_env(char **args, t_env **env);

// do_export
t_env	*name_already_exist(t_env *env, char *name_of_variable);
int		do_export(char **args, t_env **env);

// do_export_helpers
t_env	*name_already_exist(t_env *env, char *name_of_variable);
int		display_export(t_env *env);
int		add_new_env_variable(t_env **env, char *key, char *value);
int		handle_export_argument(char *arg, t_env **env);
int		is_valid_format(char *str);

// do_unset
int		do_unset(char **args, t_env *env);

// print_env
void	print_env(t_env *env);

// do_exit
int		do_exit(char **args, t_env **env);

#endif
