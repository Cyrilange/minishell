#include "../../includes/minishell.h"

void	handle_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
	if (!ft_strcmp(tokens[*i]->value, ">"))
	{
		(*i)++; //go to fitst token 
		if (tokens[*i])
			cmd->outfile = ft_strdup(tokens[*i]->value);
		(*i)++; //go to the second token
	}
	else if (!ft_strcmp(tokens[*i]->value, ">>"))
	{
		(*i)++;
		if (tokens[*i])
		{
			cmd->outfile = ft_strdup(tokens[*i]->value);
			cmd->append = 1;
		}
		(*i)++;
	}
	else if (!ft_strcmp(tokens[*i]->value, "<"))
	{
		(*i)++;
		if (tokens[*i])
			cmd->infile = ft_strdup(tokens[*i]->value);
		(*i)++;
	}
	else if (!ft_strcmp(tokens[*i]->value, "<<"))
	{
		(*i)++;
		if (tokens[*i])
		{
			cmd->infile = ft_strdup(tokens[*i]->value);
			cmd->heredoc = 1;
		}
		(*i)++;
	}
}


void	handle_token(t_token *token, char **args, int *arg_i, char **envp)
{
	process_token(token, args, arg_i, envp);
}



/*
void	condition_while_pipe(t_token **tokens, int *i, t_cmd **cmd, char ***args,
	int *arg_i, t_cmd_node **cmds, t_cmd_node **last, char **envp)
{
	if (ft_strcmp(tokens[*i]->value, "<<") == 0)
	{
		(*cmd)->heredoc = 1;
		(*i)++;
		if (tokens[*i])
		{
			(*cmd)->heredoc_delimiter = ft_strdup(tokens[*i]->value);
			(*i)++;
		}
	}
	else if (!ft_strcmp(tokens[*i]->value, "|") && tokens[*i]->quote_type == NO_QUOTE)
	{
		handle_pipe(cmds, last, cmd, args, arg_i);
		(*i)++;
	}
	else if (!ft_strcmp(tokens[*i]->value, ">") || !ft_strcmp(tokens[*i]->value, ">>") ||
			 !ft_strcmp(tokens[*i]->value, "<"))
	{
		handle_redirection(tokens, i, *cmd);
		// handle_redirection doit gérer l'incrémentation de *i, donc ne l'incrémente pas ici.
	}
	else
	{
		handle_token(tokens[*i], *args, arg_i, envp);
		(*i)++;
	}
}
*/
void	execute_pipeline(t_cmd_node *cmds, char ***envp)
{
	int		pipe_fd[2];
	int		in_fd = 0;
	pid_t	pid;

	while (cmds)
	{
		if (cmds->next && pipe(pipe_fd) < 0)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
		{
			if (cmds->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (in_fd != 0)
				dup2(in_fd, STDIN_FILENO);
			if (cmds->cmd->infile)
				redirect_infile(cmds->cmd->infile);
			if (cmds->cmd->outfile)
				redirect_outfile(cmds->cmd->outfile, cmds->cmd->append);
			close(pipe_fd[0]);
			execute_command(cmds->cmd->args, envp);
			exit(1);
		}
		close(pipe_fd[1]);
		if (in_fd != 0)
			close(in_fd);
		in_fd = pipe_fd[0];
		cmds = cmds->next;
	}
	while (wait(NULL) > 0)
		;
}

