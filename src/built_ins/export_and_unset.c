#include "../../includes/minishell.h"

// working
char *get_var_name(char *arg)
{
	int i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	char *name;
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
	return name;
}
// working
int is_in_envp(char *arg, char **envp)
{
	int i;
	char *var_name;

	i = 0;
	var_name = get_var_name(arg); // strip value of the variable, get "VAR="
	while(envp[i] != NULL) // cycle through all env vars
	{
		if (ft_strncmp(var_name, envp[i], ft_strlen(var_name)) == 0) // if arg matches env variable
		{
			if (var_name != NULL)
				free(var_name);
			return i; // return the index position of the env variable
		}
		i++;
	}
	if (var_name != NULL)
		free(var_name);
	return -1;
}


char *get_env_var_value(char *var, char **envp, int n)
{

	int var_i;
	int begin_str;
	char *value;
	var_i = is_in_envp(var, envp); // search var in evp and return its index
	if(var_i == -1)
		return NULL;
	begin_str = ft_strlen(var) + 1; // set index to cut out the "VARNAME="
	value = ft_strdup(&envp[var_i][begin_str]);
	return value;
}

int builtin_unset(char **command, char ***envp)
{
	int i;
	int var_position;
	char **newenvp;
	char *varname;
	newenvp = NULL;
	if(matrix_len(command) >= 2) // if command has 1 or more arg
	{
		i = 1;  // set i to start counting in the first arg
		while(command[i] != NULL)
		{
			if (strchr(command[i], '=') != NULL) // if name contains =, do nothing
				return 0;
			varname = get_var_name(command[i]);
			var_position = is_in_envp(varname, *envp); // search var inside envp
			if (var_position == -1) // if var was not found
				return 0;
			else
				*envp = matrix_str_dup(*envp, var_position, NULL);
			i++;
		}
	}
	return 0;
}

//working
int builtin_export(char **command, char ***envp)
{
	int i;
	int var_position;
	char **newenvp;

	newenvp = NULL;
	if(matrix_len(command) >= 2) // if export has 1 or more arg
	{
		i = 0;
		while(command[++i] != NULL) // set i to start counting in the first arg
		{
			if (ft_strrchr(command[i], '=') == NULL)
				return 0; // if no value was assigned to the variable, do nothing
			var_position = is_in_envp(command[i], *envp); // search var inside envp
			if (var_position == -1) // if var was not found
				*envp = matrix_str_add(*envp, command[i]); // append var to the envp matrix
			else // if var was found
				*envp = matrix_str_dup(*envp, var_position, command[i]);
		}
	}
	return 0;
}
