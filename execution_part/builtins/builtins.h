/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:11 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/25 20:01:42 by rmaanane         ###   ########.fr       */
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
int		do_cd(char **args, t_env *env);

// do_pwd
int		do_pwd(char **args, t_env *env);

// do_env
int		do_env(char **args, t_env **env);

// do_export
int		do_export(char **args, t_env **env);

// do_unset
int		*do_unset(char **args, t_env *env);

// print_env
void	print_env(t_env *env);

// do_exit
void	do_exit(char **args);

// create_env
t_env	*create_env(char **envp);

#endif
