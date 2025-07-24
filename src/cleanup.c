#include "../includes/minishell.h"

void cleanup(t_prompt *prompt)
{
	free_double_ptr((void **)prompt->envp);
	free(prompt);
	return;
}
