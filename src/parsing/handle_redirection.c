#include "../../includes/minishell.h"

static void	handle_output_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
	(*i)++;
	if (tokens[*i])
		cmd->outfile = ft_strdup(tokens[*i]->value);
	(*i)++;
}

static void	handle_append_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
	(*i)++;
	if (tokens[*i])
	{
		cmd->outfile = ft_strdup(tokens[*i]->value);
		cmd->append = 1;
	}
	(*i)++;
}

static void	handle_input_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
	(*i)++;
	if (tokens[*i])
		cmd->infile = ft_strdup(tokens[*i]->value);
	(*i)++;
}

static void	handle_heredoc_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
	(*i)++;
	if (tokens[*i])
	{
		cmd->infile = ft_strdup(tokens[*i]->value);
		cmd->heredoc = 1;
	}
	(*i)++;
}

void	handle_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
	if (!ft_strcmp(tokens[*i]->value, ">"))
		handle_output_redirection(tokens, i, cmd);
	else if (!ft_strcmp(tokens[*i]->value, ">>"))
		handle_append_redirection(tokens, i, cmd);
	else if (!ft_strcmp(tokens[*i]->value, "<"))
		handle_input_redirection(tokens, i, cmd);
	else if (!ft_strcmp(tokens[*i]->value, "<<"))
		handle_heredoc_redirection(tokens, i, cmd);
}
