#include "../includes/minishell.h"
#include "miniutils/miniutils.h"

int g_status;

void initialize_essential_variables(char ***envp)
{
	char *shlvl;
	char *tmp;
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

t_prompt set_initial_variables(char **envp)
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

int main(int argc, char **argv)
{
	t_prompt prompt;
	char	*input;

	(void)argc;
	argc = 1;
	prompt = set_initial_variables(argv);
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
	printf("\n EXITING\n");
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	char **strs;
// 	char **tmp;
// 	// strs = matrix_str_dup(envp, -1, NULL);
// 	strs = NULL;
// 	strs = matrix_str_add(strs, "helloworld");
// 	strs = matrix_str_dup(strs, -1, NULL);
// 	// strs = matrix_str_add(strs, "anotherworkd");
// 	(void)tmp;
// 	(void)strs;
// 	matrix_free(&strs);
// 	matrix_free(&tmp);
// 	return 0;
// }
