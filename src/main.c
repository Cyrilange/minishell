#include "../includes/minishell.h"
#include "miniutils/miniutils.h"

int g_status;

void initialize_essential_variables(char ***envp)
{
	// if (*envp == NULL)
	*envp = matrix_str_add(*envp, "MINISHELL=1");
	if (is_in_envp("PATH", *envp) == -1)
		*envp = matrix_str_add(*envp, "PATH=/usr/local/bin:/usr/bin");
	if (is_in_envp("SHLVL", *envp) == -1)
		*envp = matrix_str_add(*envp, "SHLVL=1");
	else
		replace_env_var(
			envp, "SHLVL=",
			ft_itoa(ft_atoi(get_env_var_value("SHLVL", *envp)) + 1)); // ad + 1 for each shell level
}

t_prompt set_initial_variables(char **argv, char **envp)
{
	t_prompt prompt;

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

int main(int argc, char **argv, char **envp)
{
	t_prompt prompt;
	char	*input;

	(void)argc;
	setup_signal_handlers();
	prompt = set_initial_variables(argv, envp);
	while (1)
	{
		input = get_input(&prompt);
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
	while (true)
	{
		free(input);
	}
	return (0);
}
// int main(int argc, char **argv, char **envp)
// {
// 	char **matrix = NULL;
// 	matrix = matrix_str_add(matrix, "hello");
// 	matrix_str_print(matrix);
// 	return (0);
// }
