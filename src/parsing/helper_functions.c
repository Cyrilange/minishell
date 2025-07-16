#include "../../includes/minishell.h"

t_quotes	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	if (c == '"')
		return (DOUBLE_QUOTE);
	return (NO_QUOTE);
}

t_token	*create_token(char *value, t_quotes quote_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->quote_type = quote_type;
	return (token);
}

char *handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;
	
	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (NULL);
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
	return (ft_strdup("/tmp/.heredoc_tmp"));
}

static void	setup_input_redirection(t_cmd *cmd)
{
	char	*heredoc_file;
	if (cmd->heredoc)
	{
		heredoc_file = handle_heredoc(cmd->heredoc_delimiter);
		if (!heredoc_file)
			exit(1);
		redirect_infile(heredoc_file);
		free(heredoc_file);
	}
	else if (cmd->infile)
		redirect_infile(cmd->infile);
}

static void	setup_output_redirection(t_cmd *cmd)
{
	int flags;


	if (!cmd->outfile)
		return ;
	flags = O_CREAT | O_WRONLY;
	flags |= (cmd->append) ? O_APPEND : O_TRUNC;

	int fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		write(STDERR_FILENO, "open outfile", 13);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_heredoc_if_needed(t_cmd *cmd)
{
	setup_input_redirection(cmd);
	setup_output_redirection(cmd);
}


