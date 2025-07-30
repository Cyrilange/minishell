#include "../../includes/minishell.h"

char *get_var_name(char *arg)
{
	int	  i;
	char *name;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	name = malloc(sizeof(*name) * i + 2);
	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '=';
	i++;
	name[i] = '\0';
	return (name);
}

int is_in_envp(char *arg, char **envp)
{
	int	  i;
	char *var_name;

	i = 0;
	var_name = get_var_name(arg);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_name, envp[i], ft_strlen(var_name)) == 0)
		{
			if (var_name != NULL)
				free(var_name);
			return (i);
		}
		i++;
	}
	if (var_name != NULL)
		free(var_name);
	return (-1);
}

char *get_env_var_value(char *var, char **envp)
{
	int	  var_i;
	int	  begin_str;
	char *value;

	var_i = is_in_envp(var, envp);
	if (var_i == -1)
		return (NULL);
	begin_str = ft_strlen(var) + 1;
	value = ft_strdup(&envp[var_i][begin_str]);
	return (value);
}

int builtin_unset(char **command, char ***envp)
{
	int	   i;
	int	   var_position;
	char  *varname;

	if (matrix_len(command) >= 2)
	{
		i = 1;
		while (command[i] != NULL)
		{
			if (strchr(command[i], '=') != NULL)
				return (0);
			varname = get_var_name(command[i]);
			var_position = is_in_envp(varname, *envp);
			if (var_position == -1)
				return (0);
			else
				*envp = matrix_str_dup(*envp, var_position, NULL);
			i++;
		}
	}
	return (0);
}

int builtin_export(char **command, char ***envp)
{
	int i;
	int var_position;

	if (matrix_len(command) >= 2)
	{
		i = 0;
		while (command[++i] != NULL)
		{
			if (ft_strrchr(command[i], '=') == NULL)
				return (0);
			var_position = is_in_envp(command[i], *envp);
			if (var_position == -1)
				*envp = matrix_str_add(*envp, command[i]);
			else
				*envp = matrix_str_dup(*envp, var_position, command[i]);
		}
	}
	return (0);
}
