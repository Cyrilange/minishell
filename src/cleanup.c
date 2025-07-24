#include "../includes/minishell.h"

void cleanup(t_prompt *prompt)
{
	// free_double_ptr((void **)prompt->envp);
	// matrix_free(&prompt->envp);
	free_double_ptr((void **)prompt->envp);
	return;
}
