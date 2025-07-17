#include "../../includes/minishell.h"

extern int	g_status;

char	*get_here_str(char *delim)
{
	char	*prompt;
	char	*doc;

	while (ft_strcmp(delim, prompt) != 0)
	{
		doc = ft_strjoin(doc, prompt);
		prompt = readline("> ");
		doc = ft_strjoin("\n", doc);
	}
	return (doc);
}
