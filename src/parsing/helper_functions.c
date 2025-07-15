#include "../../includes/minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

t_quotes	get_quote_type(char c)
{
	if (c == '\'')
		return SINGLE_QUOTE;
	if (c == '"')
		return DOUBLE_QUOTE;
	return NO_QUOTE;
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

char *handle_heredoc(char *delimiter)
{
    char *line;
    int fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);

    if (fd < 0)
        return NULL;

    while (1)
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line, delimiter))
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    close(fd);
    return ft_strdup("/tmp/.heredoc_tmp");
}

void handle_heredoc_if_needed(t_cmd *cmd)
{
    if (cmd->heredoc)
    {
        char *heredoc_file = handle_heredoc(cmd->heredoc_delimiter);
        if (!heredoc_file)
            exit(1);
        redirect_infile(heredoc_file);
        free(heredoc_file);
    }
    else if (cmd->infile)
    {
        redirect_infile(cmd->infile);
    }
    if (cmd->outfile)
    {
        int flags = O_CREAT | O_WRONLY;
        if (cmd->append)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;

        int fd = open(cmd->outfile, flags, 0644);
        if (fd < 0)
        {
            write(0,"open outfile", 13);
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

