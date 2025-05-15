#include "../includes/minishell.h"
/*
#define MAX_ARGS 1024


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>


typedef enum e_quotes_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quotes;

typedef struct s_data
{
	char	*input;
	char	**args;
	int		i;
}	t_data; 

typedef struct s_token {
    char     *value;
    t_quotes quote_type;
} t_token;

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

t_token *create_token(char *value, t_quotes quote_type) //fonction dans helper
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	token->value = value;
	token->quote_type = quote_type;
	return token;
} 

*/
//#-------------------------------------------------#
static t_quotes	get_quote_type(char c)
{
	if (c == '\'')
		return SINGLE_QUOTE;
	if (c == '"')
		return DOUBLE_QUOTE;
	return NO_QUOTE;
}

static t_token	*parse_redirection(t_data *data)
{
	int	start;

	start = data->i;
	if (data->input[data->i + 1] && data->input[data->i] == data->input[data->i + 1])
		data->i += 2;
	else
		data->i++;
	return create_token(ft_strndup(&data->input[start], data->i - start), NO_QUOTE);
}

static t_token	*parse_quote(t_data *data)
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
			break;
		data->i++;
	}
	len = data->i - start;
	if (data->input[data->i])
		data->i++;
	return create_token(ft_strndup(&data->input[start], len),quote);
}

static t_token	*parse_word(t_data *data)
{
	int	start;
	int	len;

	start = data->i;
	len = 0;
	while (data->input[data->i] &&
		!isspace((unsigned char)data->input[data->i]) &&
		!is_quote(data->input[data->i]) &&
		!is_special(data->input[data->i]))
	{
		data->i++;
		len++;
	}
	return create_token(ft_strndup(&data->input[start], len), NO_QUOTE);
}

static t_token	*extract_token(t_data *data)
{
	char c;

	c = data->input[data->i];
	if (c == '>' || c == '<')
		return parse_redirection(data);
	if (c == '\'' || c == '"')
		return parse_quote(data);
	return parse_word(data);
}


t_token **tokenize_input(char *input)
{
	t_data data;
	t_token **tokens;
	int i;

	data.input = input;
	data.i = 0;
	tokens = malloc(sizeof(t_token *) * MAX_ARGS);
	if (!tokens)
		return NULL;

	i = 0;
	while (input[data.i])
	{
		while (isspace(input[data.i]))
			data.i++;
		if (!input[data.i])
			break;
		tokens[i++] = extract_token(&data);
	}
	tokens[i] = NULL;
	return tokens;
}
/*
//print token
void	print_token(t_token *token)
{
	printf("Token: [%s] | Quote Type: ", token->value);
	if (token->quote_type == SINGLE_QUOTE)
		printf("SINGLE_QUOTE");
	else if (token->quote_type == DOUBLE_QUOTE)
		printf("DOUBLE_QUOTE");
	else
		printf("NO_QUOTE");
	printf("\n");
}

//test
int	main(void)
{
	char		*line1 = "echo > 'hello world' \"42 Málaga\" test";
	t_token		**tokens;
	int			i;

	tokens = tokenize_input(line1);
	if (!tokens)
	{
		printf("Error tokenisation.\n");
		return (1);
	}

	i = 0;
	while (tokens[i])
	{
		print_token(tokens[i]);
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (0);
} */