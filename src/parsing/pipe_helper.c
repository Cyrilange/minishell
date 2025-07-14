#include "../../includes/minishell.h"

static void handle_redirection(t_token **tokens, int *i, t_cmd *cmd)
{
    if (!ft_strcmp(tokens[*i]->value, ">"))
    {
        (*i)++;
        if (tokens[*i])
            cmd->outfile = ft_strdup(tokens[*i]->value);
    }
    else if (!ft_strcmp(tokens[*i]->value, ">>"))
    {
        (*i)++;
        if (tokens[*i])
        {
            cmd->outfile = ft_strdup(tokens[*i]->value);
            cmd->append = 1;
        }
    }
    else if (!ft_strcmp(tokens[*i]->value, "<"))
    {
        (*i)++;
        if (tokens[*i])
            cmd->infile = ft_strdup(tokens[*i]->value);
    }
    else if (!ft_strcmp(tokens[*i]->value, "<<"))
    {
        (*i)++;
        if (tokens[*i])
        {
            cmd->infile = ft_strdup(tokens[*i]->value);
            cmd->heredoc = 1;
        }
    }
}

static void handle_token(t_token *token, char **args, int *arg_i, char **envp)
{
    process_token(token, args, arg_i, envp);
}


static void handle_pipe(t_cmd_node **cmds, t_cmd_node **last, t_cmd **cmd, char ***args, int *arg_i)
{
    add_cmd_node(cmds, last, *cmd, *args, *arg_i);
    init_parse(cmd, args, arg_i);
}


void condition_while_pipe(t_token **tokens, int *i, t_cmd **cmd, char ***args,
    int *arg_i, t_cmd_node **cmds, t_cmd_node **last, char **envp)
{
if (!ft_strcmp(tokens[*i]->value, "|") && tokens[*i]->quote_type == NO_QUOTE)
handle_pipe(cmds, last, cmd, args, arg_i);
else if (!ft_strcmp(tokens[*i]->value, ">") || !ft_strcmp(tokens[*i]->value, ">>") ||
!ft_strcmp(tokens[*i]->value, "<") || !ft_strcmp(tokens[*i]->value, "<<"))
handle_redirection(tokens, i, *cmd);
else
handle_token(tokens[*i], *args, arg_i, envp);
(*i)++;
}
