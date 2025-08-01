#include "../includes/minishell.h"
#include "miniutils/miniutils.h"

int	g_status;

void	initialize_essential_variables(char ***envp)
{
	char	*shlvl;
	char	*tmp;
	*envp = matrix_str_add(*envp, "MINISHELL=1");
	if (is_in_envp("PATH", *envp) == -1)
		*envp = matrix_str_add(*envp, "PATH=/usr/local/bin:/usr/bin");
	if (is_in_envp("SHLVL", *envp) == -1)
		*envp = matrix_str_add(*envp, "SHLVL=1");
	else
	{
		shlvl = get_env_var_value("SHLVL", *envp); // ad + 1 for each shell level
		tmp = ft_itoa(ft_atoi(shlvl) + 1);
		replace_env_var(envp, "SHLVL=", shlvl);
		free(tmp);
		free(shlvl);
	}
}

t_prompt	set_initial_variables(char	**argv, char **envp)
{
	t_prompt	prompt;
	(void)argv;
	prompt.input = NULL;
	prompt.envp = matrix_str_dup(envp, -1, NULL);
	// if (envp == NULL)
	// envp = matrix_str_add(envp, "MINISHELL=1");
	update_pwd(&prompt.envp);
	initialize_essential_variables(&prompt.envp);
	// TODO get pid for the minishell process
	// TODO initialize essential variables
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*input;

	(void)argc;
	argc = 1;

	prompt = set_initial_variables(argv, envp);
	while (1)
	{
		set_signals_interactive();
		input = get_input(&prompt);
		set_signals_noninteractive();
		if (!input)
			continue;
		if (!*input)
		{
			free(input);
			continue;
		}
		command(input, &prompt.envp);
		free(input);
		
	}
	free_prompt(&prompt);
	rl_clear_history(); 
	return (0);
}
