#include "../../includes/minishell.h"

bool is_builtin(char *command)
{
	if (command == NULL)
		return false;
	else if (ft_strcmp(command, "cd") == 0)
		return true;
	else if (ft_strcmp(command, "echo") == 0)
		return true;
	else if (ft_strcmp(command, "env") == 0)
		return true;
	else if (ft_strcmp(command, "exit") == 0)
		return true;
	else if (ft_strcmp(command, "export") == 0)
		return true;
	else if (ft_strcmp(command, "pwd") == 0)
		return true;
	else if (ft_strcmp(command, "unset") == 0)
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
