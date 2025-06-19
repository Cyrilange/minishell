#include "../includes/minishell.h"

static void init_parse(t_cmd **cmd, char ***args, int *arg_i)
{
    *cmd = calloc(1, sizeof(t_cmd));
    *args = malloc(sizeof(char *) * (MAX_ARGS + 1));
    *arg_i = 0;
}

static void add_cmd_node(t_cmd_node **cmds, t_cmd_node **last, t_cmd *cmd, char **args, int arg_i)
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


static void process_token(t_token *token, char **args, int *arg_i)
{
    if (token->quote_type != SINGLE_QUOTE)
        args[(*arg_i)++] = expand_variables(token->value, token->quote_type);
    else
        args[(*arg_i)++] = ft_strdup(token->value);
}


t_cmd_node *parse_pipeline_tokens(t_token **tokens)
{
    t_cmd_node *cmds = NULL;
    t_cmd_node *last = NULL;
    t_cmd *cmd;
    char **args;
    int arg_i;
    int i = 0;

    init_parse(&cmd, &args, &arg_i);

    while (tokens[i])
    {
        if (!ft_strcmp(tokens[i]->value, "|") && tokens[i]->quote_type == NO_QUOTE)
        {
            add_cmd_node(&cmds, &last, cmd, args, arg_i);
            init_parse(&cmd, &args, &arg_i);
        }
        else if (!ft_strcmp(tokens[i]->value, ">"))
        {
            i++;
            if (tokens[i])
                cmd->outfile = ft_strdup(tokens[i]->value);
        }
        else if (!ft_strcmp(tokens[i]->value, ">>"))
		{
			i++;
			if (tokens[i])
			{
				cmd->outfile = ft_strdup(tokens[i]->value);
				cmd->append = 1;
			}
		}
        else if (!ft_strcmp(tokens[i]->value, "<"))
        {
            i++;
            if (tokens[i])
                cmd->infile = ft_strdup(tokens[i]->value);
        }
        else if (!ft_strcmp(tokens[i]->value, "<<"))
		{
			i++;
			if (tokens[i])
			{
				cmd->infile = ft_strdup(tokens[i]->value);
				cmd->heredoc = 1;
			}
		}
        else
            process_token(tokens[i], args, &arg_i);
        i++;
    }


    add_cmd_node(&cmds, &last, cmd, args, arg_i);
    return cmds;
}
