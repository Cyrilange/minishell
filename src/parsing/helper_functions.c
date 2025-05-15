#include "../includes/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}