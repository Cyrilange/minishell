#include "../../includes/minishell.h"

static int quotes_are_closed(const char *str)
{
    int single = 0;
    int dbl = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '\'' && dbl % 2 == 0)
            single++;
        else if (str[i] == '"' && single % 2 == 0)
            dbl++;
    }
    return (single % 2 == 0 && dbl % 2 == 0);
}

char *read_multiline_command(void)
{
    char *line = readline("minishell> ");
    char *full_line = ft_strdup(line);
    free(line);

    while (!quotes_are_closed(full_line))
    {
        line = readline(">"); // so if you fogrt the quote you have a new line 
        char *tmp = ft_strjoin(full_line, "\n");  // keep the line
        free(full_line);
        full_line = ft_strjoin(tmp, line);
        free(tmp);
        free(line);
    }
    return full_line;
}
