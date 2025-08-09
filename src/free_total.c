#include "../includes/minishell.h"

static void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_prompt(t_prompt *prompt)
{
	if (prompt->input)
		free(prompt->input);
	free_envp(prompt->envp);
}
