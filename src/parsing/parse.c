#include "../includes/minishell.h"


// Function to parse the input string into tokens

char ft_quote(t_data *input)
{
	int i = 0;
	t_data quote;

	while (input->quote[i])
	{
		if (input->quote[i] == '\'')
			return *input->quote;
		else if (input->quote[i] == '"')
			return 
		i++;
	}
	return (input->quote);
}


