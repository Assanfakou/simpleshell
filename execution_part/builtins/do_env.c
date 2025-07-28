/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:35:51 by rmaanane          #+#    #+#             */
/*   Updated: 2025/07/28 22:25:46 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	do_env(char **args, t_env **env)
{
	t_env	*walk;

	(void)args;
	walk = *env;
	while (walk)
	{
		if (walk && walk->value)
			printf("%s=%s\n", walk->name_of_variable, walk->value);
		walk = walk->next;
	}
	return (0);
}
