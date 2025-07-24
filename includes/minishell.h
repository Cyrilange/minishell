#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_ARGS 1024

#define PROMPT "\001\e[0m\e[33m\002minishell$ \001\e[0m\002"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include "./libft/libft.h"
# include "../src/miniutils/miniutils.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef enum e_quotes_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quotes;

typedef struct s_cmd
{
	char	**args; //arg for tokenising
	char	*infile; // input file
	char	*outfile; // output file
	int		heredoc; // heredoc flag
	char	*heredoc_delimiter; // delimiter for heredoc
	int		append; // append flag
	int		invalid_syntax;
}			t_cmd;

typedef struct s_cmd_node
{
	t_cmd				*cmd;
	struct s_cmd_node	*next;
}			t_cmd_node;

typedef struct s_prompt
{
	char	*input;
	char	**envp; // i need to get environment variables from the main func
	int		i; // what is this for?
	pid_t	pid; // process ID of the minishell instance
}	t_prompt;

typedef struct s_token
{
	char		*value;//prompt is memorised here
	t_quotes	quote_type;
}				t_token;
typedef struct s_parse_ctx
{
	t_cmd_node	**cmds;
	t_cmd_node	**last;
	t_cmd		*cmd;
	char		**args;
	int			arg_i;
}	t_parse_ctx;

typedef struct s_pipe_ctx
{
	t_token		**tokens;
	int			i;
	t_parse_ctx	pctx; //cmd/cmds/args
	char		**envp;
}	t_pipe_ctx;

bool		is_builtin(char *command);
void		command(char *input, char ***envp);
char		*get_input(t_prompt *prompt);
// builtins
int			builtin_env(char **envp);
int			builtin_unset(char **command, char ***envp);
int			builtin_export(char **command, char ***envp);
int			builtin_pwd(void);
int builtin_cd(char *path, char ***envp);
void replace_env_var(char ***envp, char *varname, char *value);
int			builtin_echo(char **args);
int			builtin_exit(char **command);
void	update_pwd(char ***envp);
int			is_in_envp(char *arg, char **envp);
char		*get_var_name(char *arg);
char		*get_env_var_value(char *var, char **envp);
int			is_var_char(char c);
t_quotes	get_quote_type(char c);
t_token		**tokenize_input(char *input);
t_token		*create_token(char *value, t_quotes quote_type);
char		*expand_variables(const char *str,
				t_quotes quote_type, char **envp);
int			is_special(char c);
int			is_quote(char c);
char *read_multiline_command(t_prompt *prompt);
//help variables
char		*append_str(char *base, const char *add);
char		*is_var_name(const char *str, int *len);
//heredoc
char		*handle_heredoc(char *delimiter);
void		handle_heredoc_if_needed(t_cmd *cmd);
//pipe 
t_cmd_node *parse_pipeline_tokens(t_token **tokens, char **envp, t_pipe_ctx *ctx);
void		free_cmd_list(t_cmd_node *cmds);
void		handle_token(t_token *token, char **args, int *arg_i, char **envp);
void		handle_redirection(t_token **tokens, int *i, t_cmd *cmd);
/* void		condition_while_pipe(t_token **tokens, int *i,
				t_cmd **cmd, char ***args, int *arg_i, t_cmd_node **cmds,
				t_cmd_node **last, char **envp); */
void		condition_while_pipe(t_pipe_ctx *ctx);
void		add_cmd_node(t_parse_ctx *pctx);
void		init_parse(t_parse_ctx *pctx);
void		process_token(t_token *token, char **args, int *arg_i, char **envp);
void		execute_pipeline(t_cmd_node *cmds, char ***envp);
int			execute_builtin(char **args, char ***envp);
void		redirect_outfile(char *fil, bool append);
void		redirect_infile(char *fil);
int			execute_command(char **command, char ***envp);
// search binary
char		*get_path_variable(char **envp);
char		*ret_path_if_exists(char **list_of_paths, char *program_name);
int			get_cmd_path(char **envp, char **binpath, char *cmd);
void		free_double_ptr(void **ptr);
//signal
void		setup_signal_handlers(void);

void signal_reset_prompt(int signo);
void ignore_sigquit(void);
void set_signals_interactive(void);
void signal_print_newline(int signal);
void set_signals_noninteractive(void);

void cleanup(t_prompt *prompt);

//tildes
void expand_tildes_in_tokens(t_token **tokens, char **envp);
char *expand_tilde(char *path, char **envp);

#endif
