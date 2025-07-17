#include "../../includes/minishell.h"

int builtin_env(char **envp)
{
	matrix_str_print(envp);
	return (0);
}
