#include "../../includes/minishell.h"

static t_token	*parse_redirection(t_prompt *data)
{
	int	start;

	start = data->i;
	if (data->input[data->i + 1]
		&& data->input[data->i] == data->input[data->i + 1])
		data->i += 2;
	else
		data->i++;
	return (create_token(ft_strndup(&data->input[start],
				data->i - start), NO_QUOTE));
}

static t_token	*parse_quote(t_prompt *data)
{
	int			start;
	int			len;
	t_quotes	quote;

	quote = get_quote_type(data->input[data->i]);
	data->i++;
	start = data->i;
	while (data->input[data->i])
	{
		if (get_quote_type(data->input[data->i]) == quote)
			break ;
		data->i++;
	}
	len = data->i - start;
	if (data->input[data->i])
		data->i++;
	return (create_token(ft_strndup(&data->input[start], len), quote));
}

static t_token	*parse_word(t_prompt *data)
{
	int	start;
	int	len;

	start = data->i;
	len = 0;
	while (data->input[data->i]
		&& !isspace((unsigned char)data->input[data->i])
		&& !is_quote(data->input[data->i])
		&& !is_special(data->input[data->i]))
	{
		data->i++;
		len++;
	}
	return (create_token(ft_strndup(&data->input[start], len), NO_QUOTE));
}

static t_token	*extract_token(t_prompt *data)
{
	char	c;

	c = data->input[data->i];
	if (c == '>' || c == '<')
		return (parse_redirection(data));
	if (c == '|')
	{
		data->i++;
		return (create_token(ft_strdup("|"), NO_QUOTE));
	}
	if (c == '\'' || c == '"')
		return (parse_quote(data));
	return (parse_word(data));
}

t_token	**tokenize_input(char *input)
{
	t_prompt	data;
	t_token		**tokens;
	int			i;

	data.input = input;
	data.i = 0;
	tokens = malloc(sizeof(t_token *) * MAX_ARGS);
	if (!tokens)
		return (NULL);
	i = 0;
	while (input[data.i])
	{
		while (isspace(input[data.i]))
			data.i++;
		if (!input[data.i])
			break ;
		tokens[i++] = extract_token(&data);
	}
	tokens[i] = NULL;
	return (tokens);
}
