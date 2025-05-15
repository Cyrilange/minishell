#include "../includes/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

t_token *create_token(char *value, t_quotes quote_type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->value = value;
	token->quote_type = quote_type;
	return token;
}