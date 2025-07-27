#include "execution.h"

void	free_env(t_env **env)
{
	t_env *tmp;
	t_env *next;

	if (!env || !*env)
		return;
	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name_of_variable);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}
