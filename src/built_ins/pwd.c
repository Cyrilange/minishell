#include "../../includes/minishell.h"

void replace_env_var(char ***envp, char *varname, char *value)
{
	int var_position;
	var_position = is_in_envp(varname, *envp);
	if (var_position == -1)
		*envp = matrix_str_add(*envp, ft_strjoin(varname, value));
	else
		*envp = matrix_str_dup(*envp, var_position, ft_strjoin(varname, value));
	return;
}

void update_pwd(char ***envp)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		replace_env_var(envp, "PWD=", cwd);
}

int builtin_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	return (1);
}
