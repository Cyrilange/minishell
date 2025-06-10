#include "../../includes/minishell.h"

bool is_builtin(char *command)
{
	if (command == NULL)
		return false;
	if (ft_strcmp(command, "cd"))
		return true;
	if (ft_strcmp(command, "echo"))
		return true;
	if (ft_strcmp(command, "env"))
		return true;
	if (ft_strcmp(command, "exit"))
		return true;
	if (ft_strcmp(command, "export"))
		return true;
	if (ft_strcmp(command, "pwd"))
		return true;
	if (ft_strcmp(command, "unset"))
		return true;
	return false;
}

/* int filter_nonforkable_builtins(t_prompt *prompt, t_cmd_node *cmd) */
/* { */
/* 	char **command; */
/* 	while (cmd != NULL) */
/* 	{ */
/* 		command = ((t_cmd *)cmd->cmd)->args; */
/* 		cmd = cmd->next; */
/* 	} */
/* 	if (cmd == NULL) */
/* 	{ */
/* 		return 1; */
/* 	} */
/* } */
