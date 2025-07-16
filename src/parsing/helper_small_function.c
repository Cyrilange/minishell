#include "../../includes/minishell.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');// Check if character is alphanumeric or underscore
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

