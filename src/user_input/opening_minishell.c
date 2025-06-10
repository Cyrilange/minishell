#include "../../includes/minishell.h"

int	execute_builtin(char **args, char ***envp)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return builtin_cd(args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
        return builtin_echo(args); // working
	else if (ft_strcmp(args[0], "pwd") == 0)
        return builtin_pwd(); // working
	else if (ft_strcmp(args[0], "exit") == 0)
        return builtin_exit(args); // working
	else if (ft_strcmp(args[0], "export") == 0)
        return builtin_export(args, envp); // not working
	else if (ft_strcmp(args[0], "unset") == 0)
        return builtin_unset(args, envp); // not working
	else if (ft_strcmp(args[0], "env") == 0)
        return builtin_env(*envp); // working
	return 0;
}

void command(char *input, char ***envp)
{
	t_token **tokens;
    t_cmd_node *cmds;
    t_cmd_node *tmp;

    if (!input || !*input)
        return;

    tokens = tokenize_input(input);
    if (!tokens)
        return;

    cmds = parse_pipeline_tokens(tokens);

    tmp = cmds;
    while (tmp)
    {
        printf("== Commande détectée ==\n");
        for (int j = 0; tmp->cmd->args && tmp->cmd->args[j]; j++)
	        printf("Arg[%d]: %s\n", j, tmp->cmd->args[j]);
        if (tmp->cmd->infile)
	            printf("Infile: %s\n", tmp->cmd->infile);
        if (tmp->cmd->outfile)
	        printf("Outfile: %s\n", tmp->cmd->outfile);
        if (tmp->cmd->args && tmp->cmd->args[0])
        {
            if (is_builtin(tmp->cmd->args[0]))
                execute_builtin(tmp->cmd->args, envp);
            else
            {
                fprintf(stderr, "Commande non builtin : %s\n", tmp->cmd->args[0]);
            }
        }
        tmp = tmp->next;
    }
    free_cmd_list(cmds);
    int i = 0;
    while (tokens[i])
    {
        free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
    free(tokens);
}
//acascws

void free_cmd_list(t_cmd_node *cmds)
{
    t_cmd_node *tmp;
    while (cmds)
    {
        tmp = cmds->next;
        // Libère les args
        if (cmds->cmd)
        {
            if (cmds->cmd->args)
            {
                for (int i = 0; cmds->cmd->args[i]; i++)
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


char	*get_input()
{
	t_prompt input;
	char *cwd;
	
	cwd = getenv("PWD");
	if (cwd)
		printf("\033[0;32mminishell> \033[0;34m%s\033[0m $ ", cwd);
	else
		printf("\033[0;32mminishell> \033[0m$ ");
	input.input = readline(NULL);
	if (!input.input)
	{
		printf("exit\n");
		exit(0);
	}
	if (input.input && *(input.input))
		add_history(input.input);
	return input.input;
}
