#include "../../includes/minishell.h"
#include <stdio.h>

extern int	g_status;

static void	execute_cmds(t_cmd_node *cmds, char ***envp)
{
	t_cmd_node	*tmp;
	int			j;
	pid_t		pid;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->cmd->invalid_syntax)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->cmd->heredoc || tmp->cmd->infile || tmp->cmd->outfile)
		{
			pid = fork();
			if (pid == 0)
			{
				if (tmp->cmd->heredoc)
					handle_heredoc_if_needed(tmp->cmd);
				if (tmp->cmd->infile)
					redirect_infile(tmp->cmd->infile);
				if (tmp->cmd->outfile)
					redirect_outfile(tmp->cmd->outfile, tmp->cmd->append);
				execute_command(tmp->cmd->args, envp);
				exit(1);
			}
			else
				waitpid(pid, &g_status, 0);
		}
		else
			execute_command(tmp->cmd->args, envp);
		tmp = tmp->next;
	}
}

static void	free_tokens(t_token **tokens)
{
	int	i;
	
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void	execute_parsed_cmds(t_cmd_node *cmds, char ***envp)
{
	if (cmds && cmds->next)
		execute_pipeline(cmds, envp);
	else
		execute_cmds(cmds, envp);
}

void	command(char *input, char ***envp)
{
	t_token		**tokens;
	t_cmd_node	*cmds;

	if (!input || !*input)
		return ;
	tokens = tokenize_input(input);
	if (!tokens)
		return ;
	cmds = parse_pipeline_tokens(tokens, *envp);
	execute_parsed_cmds(cmds, envp);
	free_cmd_list(cmds);
	free_tokens(tokens);
}
