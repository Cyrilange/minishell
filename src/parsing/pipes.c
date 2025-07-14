#include "../../includes/minishell.h"

void init_parse(t_cmd **cmd, char ***args, int *arg_i)
{
	*cmd = calloc(1, sizeof(t_cmd)); // Initialize command structure
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
	(*cmd)->append = 0;
	(*cmd)->heredoc = 0;
	*arg_i = 0;
	// Allocate memory for arguments, allowing for a maximum of MAX_ARGS + 1 (to include NULL terminator)
	*args = malloc(sizeof(char *) * (MAX_ARGS + 1));
	*arg_i = 0;
}

void add_cmd_node(t_cmd_node **cmds, t_cmd_node **last, t_cmd *cmd, char **args, int arg_i)
{
	args[arg_i] = NULL;
	cmd->args = args;

	t_cmd_node *node = malloc(sizeof(t_cmd_node));
	node->cmd = cmd;
	node->next = NULL;

	if (!*cmds)
		*cmds = node;
	else
		(*last)->next = node;

	*last = node;
}


void process_token(t_token *token, char **args, int *arg_i, char **envp)
{
	if (token->quote_type != SINGLE_QUOTE)
		args[(*arg_i)++] = expand_variables(token->value, token->quote_type, envp);
	else
		args[(*arg_i)++] = ft_strdup(token->value);
}



t_cmd_node *parse_pipeline_tokens(t_token **tokens, char **envp)
{
	t_cmd_node *cmds = NULL;
	t_cmd_node *last = NULL;
	t_cmd *cmd;
	char **args;
	int arg_i;
	int i;
	
	i = 0;
	init_parse(&cmd, &args, &arg_i);

	while (tokens[i])
		condition_while_pipe(tokens, &i, &cmd, &args, &arg_i, &cmds, &last, envp);
	add_cmd_node(&cmds, &last, cmd, args, arg_i);
	return cmds;
}
