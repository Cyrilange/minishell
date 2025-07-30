#include "../../includes/minishell.h" //export

char *get_var_name(char *arg)
{
	int	  i;
	char *name;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	name = malloc(sizeof(*name) * i + 2);
	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '=';
	i++;
	name[i] = '\0';
	return (name);
}

int is_in_envp(char *arg, char **envp)
{
	int	  i;
	char *var_name;

	i = 0;
	var_name = get_var_name(arg);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_name, envp[i], ft_strlen(var_name)) == 0)
		{
			if (var_name != NULL)
				free(var_name);
			return (i);
		}
		i++;
	}
	if (var_name != NULL)
		free(var_name);
	return (-1);
}

char *get_env_var_value(char *var, char **envp)
{
	int	  var_i;
	int	  begin_str;
	char *value;

	var_i = is_in_envp(var, envp);
	if (var_i == -1)
		return (NULL);
	begin_str = ft_strlen(var) + 1;
	value = ft_strdup(&envp[var_i][begin_str]);
	return (value);
}

int builtin_unset(char **command, char ***envp)
{
	int	   i;
	int	   var_position;
	char  *varname;

	if (matrix_len(command) >= 2)
	{
		i = 1;
		while (command[i] != NULL)
		{
			if (strchr(command[i], '=') != NULL)
				return (0);
			varname = get_var_name(command[i]);
			var_position = is_in_envp(varname, *envp);
			if (var_position == -1)
				return (0);
			else
				*envp = matrix_str_dup(*envp, var_position, NULL);
			i++;
		}
	}
	return (0);
}

int builtin_export(char **command, char ***envp)
{
	int i;
	int var_position;

	if (matrix_len(command) >= 2)
	{
		i = 0;
		while (command[++i] != NULL)
		{
			if (ft_strrchr(command[i], '=') == NULL)
				return (0);
			var_position = is_in_envp(command[i], *envp);
			if (var_position == -1)
				*envp = matrix_str_add(*envp, command[i]);
			else
				*envp = matrix_str_dup(*envp, var_position, command[i]);
		}
	}
	return (0);
}


#include "../../includes/minishell.h" //tokenise

static t_token	*parse_redirection(t_prompt *data)
{
	int	start;

	start = data->i;
	if (data->input[data->i + 1]
		&& data->input[data->i] == data->input[data->i + 1])
		data->i += 2;
	else
		data->i++;
	return (create_token(ft_strndup(&data->input[start],
				data->i - start), NO_QUOTE));
}

static t_token	*parse_quote(t_prompt *data)
{
	int			start;
	int			len;
	t_quotes	quote;

	quote = get_quote_type(data->input[data->i]);
	data->i++;
	start = data->i;
	while (data->input[data->i])
	{
		if (get_quote_type(data->input[data->i]) == quote)
			break ;
		data->i++;
	}
	len = data->i - start;
	if (data->input[data->i])
		data->i++;
	return (create_token(ft_strndup(&data->input[start], len), quote));
}

static t_token	*parse_word(t_prompt *data)
{
	int	start;
	int	len;

	start = data->i;
	len = 0;
	while (data->input[data->i]
		&& !isspace((unsigned char)data->input[data->i])
		&& !is_quote(data->input[data->i])
		&& !is_special(data->input[data->i]))
	{
		data->i++;
		len++;
	}
	return (create_token(ft_strndup(&data->input[start], len), NO_QUOTE));
}

static int is_assignment_start(t_prompt *data)
{
	int temp_i = data->i;

	if (!isalpha(data->input[temp_i]) && data->input[temp_i] != '_')
		return (0);
	while (data->input[temp_i] && (isalnum(data->input[temp_i]) || data->input[temp_i] == '_'))
		temp_i++;
	return (data->input[temp_i] == '=');
}
static t_token *parse_assignment(t_prompt *data)
{
	char	quote;
	char	*result;
	int		pos;
	
	pos = 0;
	result = malloc(1000);
	while (data->input[data->i] && data->input[data->i] != '=')
		result[pos++] = data->input[data->i++];
	
	if (data->input[data->i] == '=')
	{
		result[pos++] = data->input[data->i++];
		if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		{
			quote = data->input[data->i++];
			while (data->input[data->i] && data->input[data->i] != quote)
				result[pos++] = data->input[data->i++];
			if (data->input[data->i] == quote)
				data->i++;
		}
		else
		{
			while (data->input[data->i] && !isspace(data->input[data->i]) 
				   && !is_special(data->input[data->i]))
				result[pos++] = data->input[data->i++];
		}
	}
	
	result[pos] = '\0';
	char *final_result = ft_strdup(result);
	free(result);
	return create_token(final_result, NO_QUOTE);
}

static t_token *extract_token(t_prompt *data)
{
	char c;
	
	c = data->input[data->i];	
	if (is_assignment_start(data))
		return (parse_assignment(data));
	if (c == '>' || c == '<')
		return (parse_redirection(data));
	if (c == '|')
	{
		data->i++;
		return (create_token(ft_strdup("|"), NO_QUOTE));
	}
	if (c == '\'' || c == '"')
		return (parse_quote(data));
	return (parse_word(data));
}

t_token	**tokenize_input(char *input)
{
	t_prompt	data;
	t_token		**tokens;
	int			i;

	data.input = input;
	data.i = 0;
	tokens = malloc(sizeof(t_token *) * MAX_ARGS);
	if (!tokens)
		return (NULL);
	i = 0;
	while (input[data.i])
	{
		while (isspace(input[data.i]))
			data.i++;
		if (!input[data.i])
			break ;
		tokens[i++] = extract_token(&data);
	}
	tokens[i] = NULL;
	return (tokens);
}


#include "../../includes/minishell.h" //varaib;e

extern int g_status;

static char *process_special_variable(int *i, char *result)
{
	char *status_str;

	status_str = ft_itoa(g_status);
	result = append_str(result, status_str);
	free(status_str);
	(*i)++;
	return (result);
}

static char *process_variable_name(const char *str, int *i, char *result, char **envp)
{
	int	  len;
	char *var_name;
	char *value;
	bool  freevalue;

	len = 0;
	var_name = is_var_name(&str[*i], &len);
	if (var_name)
	{
		value = get_env_var_value(var_name, envp);
		freevalue = true;
		free(var_name);
		if (!value)
		{
			freevalue = false;
			value = "";
		}
		result = append_str(result, value);
		*i += len;
		if (freevalue == true)
			free(value);
	}
	return (result);
}

static char *process_dollar(const char *str, int *i, char *result, char **envp)
{
	(*i)++;
	if (str[*i] == '?')
		result = process_special_variable(i, result);
	else if (isalpha(str[*i]) || str[*i] == '_')
		result = process_variable_name(str, i, result, envp);
	else
		result = append_str(result, "$");
	return (result);
}

static char *process_normal_char(char c, char *result)
{
	char tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	char *r = append_str(result, tmp);
	return (r);
}

char *expand_variables(const char *str, t_quotes quote_type, char **envp)
{
	int	  i;
	char *result;

	i = 0;
	if (quote_type == SINGLE_QUOTE)
		return (ft_strdup(str));
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && quote_type != SINGLE_QUOTE)
			result = process_dollar(str, &i, result, envp);
		else
		{
			result = process_normal_char(str[i], result);
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

#include "../../includes/minishell.h" condition pipe

static void handle_pipe(t_pipe_ctx *ctx)
{
	add_cmd_node(&ctx->pctx);
	init_parse(&ctx->pctx);
}

static int is_pipe_token(t_token *token)
{
	return (!ft_strcmp(token->value, "|") && token->quote_type == NO_QUOTE);
}

static int is_redirect_token(t_token *token)
{
	return (!ft_strcmp(token->value, ">") || !ft_strcmp(token->value, ">>") ||
			!ft_strcmp(token->value, "<") || !ft_strcmp(token->value, "<<"));
}

void condition_while_pipe(t_pipe_ctx *ctx)
{
	t_token *token;

	token = ctx->tokens[ctx->i];
	if (!ft_strcmp(token->value, "<<"))
	{
		ctx->pctx.cmd->heredoc = 1;
		ctx->i++;
		if (ctx->tokens[ctx->i])
			ctx->pctx.cmd->heredoc_delimiter = ft_strdup(ctx->tokens[ctx->i++]->value);
	}
	else if (is_pipe_token(token))
	{
		handle_pipe(ctx);
		ctx->i++;
	}
	else if (is_redirect_token(token))
		handle_redirection(ctx->tokens, &ctx->i, ctx->pctx.cmd);
	else
	{
		handle_token(token, ctx->pctx.args, &ctx->pctx.arg_i, ctx->envp);
		ctx->i++;
	}
}


//opening minishell

#include "../../includes/minishell.h"
#include <stdio.h>

extern int g_status;

static void handle_cmd_node(t_cmd_node *node, char ***envp)
{
	pid_t pid;

	if (node->cmd->invalid_syntax)
		return;
	if (node->cmd->heredoc || node->cmd->infile || node->cmd->outfile)
	{
		pid = fork();
		if (pid == 0)
		{
			if (node->cmd->heredoc)
				handle_heredoc_if_needed(node->cmd);
			if (node->cmd->infile)
				redirect_infile(node->cmd->infile);
			if (node->cmd->outfile)
				redirect_outfile(node->cmd->outfile, node->cmd->append);
			execute_command(node->cmd->args, envp);
			exit(1);
		}
		else
		{
			waitpid(pid, &g_status, 0);
		}
	}
	else
		execute_command(node->cmd->args, envp);
}

static void execute_cmds(t_cmd_node *cmds, char ***envp)
{
	t_cmd_node *tmp;

	tmp = cmds;
	while (tmp)
	{
		handle_cmd_node(tmp, envp);
		tmp = tmp->next;
	}
}

static void free_tokens(t_token **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void execute_parsed_cmds(t_cmd_node *cmds, char ***envp)
{
	if (cmds && cmds->next)
		execute_pipeline(cmds, envp);
	else
		execute_cmds(cmds, envp);
}

void command(char *input, char ***envp)
{
	t_token	  **tokens;
	t_cmd_node *cmds;
	t_pipe_ctx *ctx;

	ctx = malloc(sizeof(t_pipe_ctx));
	if (!input || !*input)
		return;
	tokens = tokenize_input(input);
	if (!tokens)
		return;
	cmds = parse_pipeline_tokens(tokens, *envp, ctx);
	expand_tildes_in_tokens(tokens, *envp);
	execute_parsed_cmds(cmds, envp);
	update_pwd(envp);
	free_cmd_list(cmds);
	free_tokens(tokens);
	free(ctx);
}


//pipe

#include "../../includes/minishell.h"

void init_parse(t_parse_ctx *pctx)
{
	int i;

	i = 0;
	pctx->cmd = calloc(1, sizeof(t_cmd));
	if (!pctx->cmd)
		return;
	free(pctx->cmd->args);
	pctx->cmd->args = NULL;
	pctx->cmd->infile = NULL;
	pctx->cmd->outfile = NULL;
	pctx->cmd->append = 0;
	pctx->cmd->heredoc = 0;
	pctx->cmd->heredoc_delimiter = NULL;
	pctx->cmd->invalid_syntax = 0;
	pctx->args = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (!pctx->args)
		return;
	while (i <= MAX_ARGS)
	{
		pctx->args[i] = NULL;
		i++;
	}
	pctx->arg_i = 0;
}

void add_cmd_node(t_parse_ctx *pctx)
{
	t_cmd_node *node;

	pctx->args[pctx->arg_i] = NULL;
	pctx->cmd->args = pctx->args;
	node = malloc(sizeof(t_cmd_node));
	if (!node)
	{
		free(pctx->cmd->args);
		free(pctx->cmd);
		return;
	}
	node->cmd = pctx->cmd;
	node->next = NULL;
	if (!*pctx->cmds)
		*pctx->cmds = node;
	else
		(*pctx->last)->next = node;
	*pctx->last = node;
}

void process_token(t_token *token, char **args, int *arg_i, char **envp)
{
	if (token->quote_type != SINGLE_QUOTE)
		args[(*arg_i)++] = expand_variables(token->value, token->quote_type, envp);
	else
		args[(*arg_i)++] = ft_strdup(token->value);
}

t_cmd_node *parse_pipeline_tokens(t_token **tokens, char **envp, t_pipe_ctx *ctx)
{
	t_cmd_node *cmds;
	t_cmd_node *last;

	cmds = NULL;
	last = NULL;
	ctx->tokens = tokens;
	ctx->i = 0;
	ctx->pctx.cmds = &cmds;
	ctx->pctx.last = &last;
	init_parse(&ctx->pctx);
	ctx->envp = envp;
	while (ctx->tokens[ctx->i])
		condition_while_pipe(ctx);
	add_cmd_node(&ctx->pctx);
	// free_double_ptr((void **)ctx.pctx.args);
	// free_double_ptr((void **)ctx.pctx.args);
	return (cmds);
}


//hadle heredoc

#include "../../includes/minishell.h"

char	*handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	return (ft_strdup("/tmp/.heredoc_tmp"));
}

static void	setup_input_redirection(t_cmd *cmd)
{
	char	*heredoc_file;

	if (cmd->heredoc)
	{
		heredoc_file = handle_heredoc(cmd->heredoc_delimiter);
		if (!heredoc_file)
			exit(1);
		redirect_infile(heredoc_file);
		free(heredoc_file);
	}
	else if (cmd->infile)
		redirect_infile(cmd->infile);
}

static void	setup_output_redirection(t_cmd *cmd)
{
	int	flags;
	int	fd;

	if (!cmd->outfile)
		return ;
	flags = O_CREAT | O_WRONLY;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		write(STDERR_FILENO, "open outfile", 13);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_heredoc_if_needed(t_cmd *cmd)
{
	setup_input_redirection(cmd);
	setup_output_redirection(cmd);
}



