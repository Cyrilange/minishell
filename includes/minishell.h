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
#include "./libft.h"

typedef enum e_quotes_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quotes;

typedef struct s_data
{
	char	*input;
	int		i;
}	t_data;

typedef struct s_token {
    char     *value;
    t_quotes quote_type;
} t_token;

typedef struct s_cmd {
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
}	t_cmd;


int	is_builtin(const char *cmd);
void command(char *input);
char *get_input();



int ft_cd(char *path);


void update_pwd(void);
int ft_pwd(void);


int ft_echo(char **args);
t_token **tokenize_input(char *input);
t_token *create_token(char *value, t_quotes quote_type);
char *expand_variables(const char *str, t_quotes quote_type);
int	is_special(char c);
int	is_quote(char c);
#endif