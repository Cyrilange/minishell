#include "../../includes/minishell.h"

void	free_cmd_list(t_cmd_node *cmds)
{
	t_cmd_node	*tmp;
	int			i;

	i = -1;
	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->cmd)
		{
			if (cmds->cmd->args)
			{
				while (cmds->cmd->args[++i])
					free(cmds->cmd->args[i]);
				free(cmds->cmd->args);
			}
			free(cmds->cmd->infile);
			free(cmds->cmd->outfile);
			free(cmds->cmd);
		}
		free(cmds);
		cmds = tmp;
	}
}

char	*get_input(t_prompt *prompt)
{
	char	*cwd;

	cwd = getenv("PWD");
	if (cwd)
		printf("\033[0;32mminishell> \033[0;34m%s\033[0m $ ", cwd);
	else
		printf("\033[0;32mminishell> \033[0m$ ");
	prompt->input = read_multiline_command();
	if (!prompt->input)
	{
		printf("exit\n");
		exit(0);
	}
	if (*(prompt->input))
		add_history(prompt->input);
	return (prompt->input);
}
