#include "../../includes/minishell.h"

void	free_cmd_list(t_cmd_node *cmds)
{
	t_cmd_node	*tmp;
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
/*
char	*get_input(t_prompt *prompt)
{
	char	*cwd;
    char    *input;
    char    *prompt_str;

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
} */

char	*get_input(t_prompt *prompt)
{
	char	*cwd;
	char	*prompt_str;
	char	*input;

	cwd = getenv("PWD");
	if (cwd)
		prompt_str = ft_strjoin("\033[0;32mminishell> \033[0;34m", cwd);
	else
		prompt_str = ft_strdup("\033[0;32mminishell> \033[0m");
	char *tmp = prompt_str;
	prompt_str = ft_strjoin(tmp, "\033[0m $ ");
	free(tmp);
	input = read_multiline_command(prompt_str);
	free(prompt_str);
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

