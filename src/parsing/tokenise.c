#include "../includes/minishell.h"

static t_token *parse_redirection(t_prompt *data)
{
	int start;
	
	start = data->i;
	// If the current and next characters are the same, it's a double redirection
	if (data->input[data->i + 1] && data->input[data->i] == data->input[data->i + 1])
		data->i += 2; // move index forward by 2
	else
		data->i++; // otherwise, single redirection, move forward by 1
	return create_token(ft_strndup(&data->input[start], data->i - start), NO_QUOTE);// Create a token for the redirection operator
}

// Parses quoted strings: 'single quotes' or "double quotes"
static t_token *parse_quote(t_prompt *data)
{
	int			start;
	int			len;
	t_quotes	quote;

	quote = get_quote_type(data->input[data->i]);// Detect the type of quote (' or ")
	data->i++; // skip the opening quote
	start = data->i;// Store the starting index of the quoted content
	while (data->input[data->i])// Loop until the matching closing quote is found
	{
		if (get_quote_type(data->input[data->i]) == quote)// Check if the current character matches the opening quote type
			break;
		data->i++;// Move to the next character
	}
	len = data->i - start;
	if (data->input[data->i])// Skip the closing quote if it exists
		data->i++;
	return create_token(ft_strndup(&data->input[start], len), quote);// Create a token with the quoted content and its quote type
}

// Parses normal words (commands, arguments, etc.)
static t_token *parse_word(t_prompt *data)
{
	int start;
	int	len;
	
	start = data->i;// Store the starting index of the word
	len = 0;
	while (data->input[data->i] &&// Loop until reaching space, quote, or a special character
		!isspace((unsigned char)data->input[data->i]) &&
		!is_quote(data->input[data->i]) &&
		!is_special(data->input[data->i]))
	{
		data->i++;// Move to the next character
		len++;// Increment the length of the word
	}	
	return create_token(ft_strndup(&data->input[start], len), NO_QUOTE);// Create a token for the word
}

static t_token	*extract_token(t_prompt *data)// Determines the type of token based on the current character and calls the appropriate parsing function
{
	char c;

	c = data->input[data->i];// Get the current character from the input string.
	// Case 1: Redirection symbols (exemple., ">", ">>", "<", "<<")
    // If the current character is '>' or '<', we may be starting a redirection operator.
    // This can be either a single or double redirection.
	if (c == '>' || c == '<')
		return parse_redirection(data);// Handle and return the redirection token
	// Case 2: Pipe character '|'
    // If we encounter a pipe, it represents a command separator in a pipeline.
	if (c == '|')
	{
		data->i++; // Skip the pipe character
		return create_token(ft_strdup("|"), NO_QUOTE);// Create a token with value "|" and no quotes

	}
	// Case 3: Quoted strings
    // If the character is a quote (single or double), we parse it accordingly.
	if (c == '\'' || c == '"')
		return parse_quote(data);
	// Case 4: Regular word 
    // If it's none of the above, assume it's a regular word 
	return parse_word(data);
}



t_token **tokenize_input(char *input) // Tokenizes the input string into an array of t_token pointers
{
	t_prompt data;        // Temporary struct to track parsing state
	t_token **tokens;     // Array of token pointers to return
	int i;                // Token index

	// Initialize the input for parsing
	data.input = input;   // The full string to be tokenized
	data.i = 0;           // Start index for scanning the input
	// Allocate memory for the maximum possible number of tokens
	// MAX_ARGS is a predefined constant (like 1024), representing the max number of tokens expected
	tokens = malloc(sizeof(t_token *) * MAX_ARGS);
	if (!tokens)
		return NULL;
	i = 0;// Start filling the tokens array at index 0
	// Loop through the input string
	while (input[data.i])
	{
		while (isspace(input[data.i]))// Skip all whitespace characters between tokens
			data.i++;
		if (!input[data.i])// If we reach the end after skipping spaces, break out of the loop
			break;
		tokens[i++] = extract_token(&data);// Use `extract_token()` to detect and create the next token based on the current character
	}
	tokens[i] = NULL;	// Null-terminate the token array (important for later iteration)
	return tokens;// return the array of tokens
}
