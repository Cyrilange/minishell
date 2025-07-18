#include "../includes/minishell.h"
#include "miniutils/miniutils.h"

int	g_status;

t_prompt	set_initial_variables(char **argv, char **envp)
{
	t_prompt	prompt;

	prompt.input = NULL;
	prompt.envp = matrix_str_dup(envp, -1, NULL);
   //TODO get pid for the minishell process
   //TODO initialize essential variables
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	int			i;
	int			j;
	char		**matrix;
	char		*input;

	(void) argc;
	prompt = set_initial_variables(argv, envp);
	i = 0;
	j = 1;
	while (1)
	{
		input = get_input(&prompt);
		if (!input || !*input)
		{
			free(input);
			continue ;
		}
		command(input, &prompt.envp);
		free(input);
	}
	return (0);
}
