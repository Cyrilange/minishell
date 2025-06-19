#ifndef MINISHELL_H
#define MINISHELL_H
#define MAX_ARGS 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <string.h>
#include "./libft/libft.h"
#include "../src/miniutils/miniutils.h"

typedef enum e_quotes_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quotes;

typedef struct s_prompt
{
	char	*input;
	char    **envp; // i need to get environment variables from the main func
	int		i; // what is this for?
	pid_t pid; // process ID of the minishell instance
}	t_prompt;

typedef struct s_token {
    char     *value;  //prompt is memorised here
    t_quotes quote_type;
} t_token;

typedef struct s_cmd {
	char	**args; //arg for tokenising
	char	*infile; // input file
	char	*outfile; // output file
	int		heredoc; // heredoc flag
	int		append; // append flag
}	t_cmd;

typedef struct s_cmd_node { //use for pipe to c reate a next cmd
	t_cmd *cmd;
	struct s_cmd_node *next;
} t_cmd_node;

bool is_builtin(char *command);
void command(char *input, char ***envp);
char *get_input();


// builtins
int builtin_env(char **envp);
int builtin_unset(char **command, char ***envp);
int builtin_export(char **command, char ***envp);
int builtin_pwd(void);
int builtin_cd(char *path);
int builtin_echo(char **args);
int builtin_exit(char **command);

void update_pwd(void);


int is_in_envp(char *arg, char **envp);
char *get_var_name(char *arg);

t_quotes	get_quote_type(char c);
t_token **tokenize_input(char *input);
t_token *create_token(char *value, t_quotes quote_type);
char *expand_variables(const char *str, t_quotes quote_type);
int	is_special(char c);
int	is_quote(char c);
t_cmd_node *parse_pipeline_tokens(t_token **tokens);
void free_cmd_list(t_cmd_node *cmds);
#endif
