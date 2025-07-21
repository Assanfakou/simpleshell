#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "../../lexer/parce.h"


//main.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);

//do_echo
// int	ft_strcmp(char *s1, char *s2);
int do_echo(char **args, t_env *env);


//do_cd
int do_cd(char **args, t_env *env);

//do_pwd
int do_pwd(char **args, t_env *env);

//do_env
int do_env(char **args, t_env **env);

//do_export
int do_export(char **args, t_env **env);

//do_unset
int *do_unset(char **args, t_env *env);

//print_env
void print_env(t_env *env);

//do_exit
void	do_exit(char **args, int *exit_status);

//create_env
t_env *create_env(char **envp);

#endif
