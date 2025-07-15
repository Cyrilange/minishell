#include "../includes/minishell.h"
#include "miniutils/miniutils.h"
#include <stdio.h>
#include <unistd.h>

int g_status;

t_prompt set_initial_variables(char **argv, char **envp)
{
   t_prompt prompt;
   prompt.input = NULL;
   prompt.envp = matrix_str_dup(envp, -1, NULL);
   //TODO get pid for the minishell process
   //TODO initialize essential variables
   return prompt;
}

t_prompt initialize_variables(t_prompt prompt, char *str, char **argv)
{

}

int main(int argc, char **argv, char **envp)
{
	(void) argc; // Not in use right now
	t_prompt prompt;
	prompt = set_initial_variables(argv, envp);
	/* char **dup =  matrix_str_dup(prompt.envp); */
	/* dup = matrix_str_add(dup, "hello"); */
	/* matrix_str_print(dup); */
	int i = 0;
	int j = 1;
	char **matrix;
	while (1)
	{
		char *input = get_input(&prompt);
		if (!input || !*input) // If input is empty or NULL, continue to the next iteration
		{
			free(input);
			continue;
		}
		command(input, &prompt.envp);
		/* is_in_envp("hi", prompt.envp); */
		/* matrix =  matrix_str_add(prompt.envp, "hello"); */
		free(input); 
	}
	return 0;
}
