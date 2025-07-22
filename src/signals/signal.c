#include "../../includes/minishell.h"

extern int  g_status;

static void	sigint_handler(int signo)
{
	(void)signo;
	g_status = 130;
	write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);
    g_status = 130;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
