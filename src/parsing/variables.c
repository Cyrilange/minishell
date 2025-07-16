#include "../../includes/minishell.h"

extern int	g_status;

static char	*is_var_name(const char *str, int *len)
{
	int i;

	i = 0;
	while (str[i] && is_var_char(str[i]))// Continue while characters are valid for variable names
		i++;
	*len = i;// Set the length of the variable name
	if (i == 0 || (i == 1 && str[0] == '_'))// If no valid characters or only underscore, return NULL
	{
		return NULL;
	}
	return	ft_strndup(str, i);// Return a duplicate of the variable name
}

static char	*append_str(char *base, const char *add)// Append a string to another, allocating new memory if necessary
{
	if (!base)
		return strdup(add);
	char *new_str = malloc(ft_strlen(base) + ft_strlen(add) + 1);// Allocate memory for the new string
	if (!new_str)
	{
		free(base);
		return NULL;
	}
	ft_strcpy(new_str, base);// Copy the base string to the new string
	ft_strcat(new_str, add);// Append the additional string
	free(base);// Free the base string
	return new_str;// Return the new string
}

char	*expand_variables(const char *str, t_quotes quote_type, char **envp)// Expand variables in a string based on the quote type
{
	int		i;
	int		len;
	char	*result;

	if (quote_type == SINGLE_QUOTE)
		return ft_strdup(str);// If single quotes, return the string as is

	result = ft_strdup("");// Initialize result as an empty string
	i = 0;
	while (str[i])// Iterate through the string
	{
		if (str[i] == '$' && quote_type != SINGLE_QUOTE) // If we encounter a dollar sign and not in single quotes
		{
			i++;
			if (str[i] == '?') //check for sepcial cases
			{
				result = ft_itoa(g_status);// Append exit status
				i++;
			}
			else if (isalpha(str[i]) || str[i] == '_') // If the next character is a valid variable name start
			{
				len = 0;
				char *var_name = is_var_name(&str[i], &len); // Extract the variable name
				char *value = get_env_var_value(var_name, envp); // Get the value of the variable from the environment
				free(var_name);
				if (!value)
					value = "";
				result = append_str(result, value); // Append the variable value to the result
				i += len;  // Move the index forward by the length of the variable name
			}
			else
				result = append_str(result, "$"); // If not a valid variable name, just append the dollar sign
		}
		else
		{
			char tmp[2] = {str[i], 0}; // Create a temporary string for the current character
			result = append_str(result, tmp); 	// Append the current character to the result
			if (!result) // Check if memory allocation was successful
				return NULL;
			i++;
		}
		if (!result)
			return NULL;
	}
	return result; // Return the final expanded string
}
