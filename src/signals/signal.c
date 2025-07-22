#include "../../includes/minishell.h"

extern int g_status;

void signal_reset_prompt(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void set_signals_interactive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_reset_prompt);
}

void set_signals_noninteractive(void)
{
	signal(SIGINT, signal_print_newline);
	signal(SIGQUIT, signal_print_newline);
}
