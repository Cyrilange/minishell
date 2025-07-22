#include "../../includes/minishell.h"

void free_cmd_list(t_cmd_node *cmds)
{
	t_cmd_node *tmp;
	int			i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->cmd)
		{
			if (cmds->cmd->args)
			{
				i = 0;
				while (cmds->cmd->args[i])
				{
					free(cmds->cmd->args[i]);
					i++;
				}
				free(cmds->cmd->args);
			}
			free(cmds->cmd->infile);
			free(cmds->cmd->outfile);
			free(cmds->cmd->heredoc_delimiter);
			free(cmds->cmd);
		}
		free(cmds);
		cmds = tmp;
	}
}

char *get_input(t_prompt *prompt)
{
	char *input;

	input = read_multiline_command();
	if (!input)
	{
		printf("exit\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	prompt->input = input;
	return input;
}
