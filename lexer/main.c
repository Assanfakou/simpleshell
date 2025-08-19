/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:07:44 by hfakou            #+#    #+#             */
/*   Updated: 2025/08/19 16:24:53 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/main.h"
#include "parce.h"

char	*join_and_free_two(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

void	free_exit(char *input, t_env *env)
{
	write(1, "exit\n", 5);
	free(input);
	free_t_env(env);
}

void	check_bofore_execute(t_lexer *lex, t_env **env, char *input)
{
	t_cmd	*head;

	head = NULL;
	*lex = lexer_new(input);
	head = build_cmd_list(lex, *env);
	if (!g_herdoc_stop && head)
		f_main(head, env, input);
	else
	{
		free(input);
		free_t_cmd(head);
	}
}
char *generate_prompt(void)
{
	char *last;
	char *second;
	char *join;
	char *forth;

	join = ft_strjoin(COLORE"(hfakou_and_rmaanane_shell ", getcwd(NULL, 0));
	second = ft_strjoin(join, "  (");	
	last = join_and_free_two(second, ft_itoa(status_get()));
	forth = ft_strjoin(last, ") $ "RESET);
	free(last);
	return (forth);
}	
int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_lexer	lexer;
	char	*input;
	char *prompt;

	(void)ac;
	(void)av;
	env = _create_env(envp);
	while (1)
	{
		handle_signals_interactive();
		prompt = generate_prompt(); 
		input = readline(prompt);
		free(prompt);
		if (!input)
			return (free_exit(input, env), status_get());
		add_history(input);
		g_herdoc_stop = false;
		if (!find_error(lexer, input))
			check_bofore_execute(&lexer, &env, input);
		else
			free(input);
	}
}
