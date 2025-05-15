#include "../includes/minishell.h"

/*#define MAX_ARGS 1024


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
//#include "./libft.h"

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
}	t_data; */

static char	*parse_redirection(t_data *data)
{
	int	start;

	start = data->i;
	if (data->input[data->i + 1] && data->input[data->i] == data->input[data->i + 1])
		data->i += 2;
	else
		data->i++;
	return ft_strndup(&data->input[start], data->i - start);
}

static char	*parse_quote(t_data *data)
{
	int		start;
	int		len;
	t_quotes	quote;

	quote = NO_QUOTE;
	if (data->input[data->i] == '\'')
		quote = SINGLE_QUOTE;
	else if (data->input[data->i] == '"')
		quote = DOUBLE_QUOTE;
	data->i++;
	start = data->i;
	while (data->input[data->i])
	{
		if ((quote == SINGLE_QUOTE && data->input[data->i] == '\'') ||
			(quote == DOUBLE_QUOTE && data->input[data->i] == '"'))
			break;
		data->i++;
	}
	len = data->i - start;
	if (data->input[data->i])
		data->i++;
	return ft_strndup(&data->input[start], len);
}

static char	*parse_word(t_data *data)
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
	return ft_strndup(&data->input[start], len);
}

static char	*extract_token(t_data *data)
{
	char c;

	c = data->input[data->i];
	if (c == '>' || c == '<')
		return parse_redirection(data);
	if (c == '\'' || c == '"')
		return parse_quote(data);
	return parse_word(data);
}


char **tokenize_input(char *input)
{
	t_data data;
	int arg_i;
	data.input;
	data.args;

	data.input = input;
	arg_i = 0;
	data.i = 0;
	data.args = malloc(sizeof(char *) * MAX_ARGS);
	if (!data.args)
		return NULL;

	while (input[data.i])
	{
		while (isspace(input[data.i]))
			data.i++;
		if (!input[data.i])
			break;
		data.args[arg_i++] = extract_token(&data);
	}
	data.args[arg_i] = NULL;
	return data.args;
}
/*

int main(void)
{
	char input[1024];

	while (1)
	{
		printf("\nEnter CMD : ");
		if (!fgets(input, sizeof(input), stdin))
			break;
		input[strcspn(input, "\n")] = '\0';

		char **tokens = tokenize_input(input);
		if (!tokens)
		{
			printf("Erreur d'allocation\n");
			continue;
		}

		printf("Tokens :\n");
		for (int j = 0; tokens[j]; j++)
			printf("  [%d]: %s\n", j, tokens[j]);
		for (int j = 0; tokens[j]; j++)
			free(tokens[j]);
		free(tokens);
	}
	return 0;
}  */