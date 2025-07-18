#include "../../includes/minishell.h"

extern int	g_status;

static char	*process_special_variable(int *i, char *result)
{
	char	*status_str;

	status_str = ft_itoa(g_status);
	result = append_str(result, status_str);
	free(status_str);
	(*i)++;
	return (result);
}

static char	*process_variable_name(const char *str, int *i,
			char *result, char **envp)
{
	int		len;
	char	*var_name;
	char	*value;

	len = 0;
	var_name = is_var_name(&str[*i], &len);
	if (var_name)
	{
		value = get_env_var_value(var_name, envp);
		free(var_name);
		if (!value)
			value = "";
		result = append_str(result, value);
		*i += len;
	}
	return (result);
}

static char	*process_dollar(const char *str, int *i, char *result, char **envp)
{
	(*i)++;
	if (str[*i] == '?')
		result = process_special_variable(i, result);
	else if (isalpha(str[*i]) || str[*i] == '_')
		result = process_variable_name(str, i, result, envp);
	else
		result = append_str(result, "$");
	return (result);
}

static char	*process_normal_char(char c, char *result)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	return (append_str(result, tmp));
}

char	*expand_variables(const char *str, t_quotes quote_type, char **envp)
{
	int		i;
	char	*result;

	i = 0;
	if (quote_type == SINGLE_QUOTE)
		return (ft_strdup(str));
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && quote_type != SINGLE_QUOTE)
			result = process_dollar(str, &i, result, envp);
		else
		{
			result = process_normal_char(str[i], result);
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}
