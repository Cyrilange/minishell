#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

extern int	g_status;

void	redirect_outfile(char *fil, bool append)
{
	int	outfile_fd;

	if (append == true)
		outfile_fd = open(fil, O_WRONLY | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR);
	else
		outfile_fd = open(fil, O_WRONLY | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	redirect_infile(char *fil)
{
	int	infile_fd;

	infile_fd = open(fil, O_RDONLY);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}

bool	is_absolute(char *command)
{
	if (command[0] == '/')
		return (true);
	return (false);
}

int	execute_command(char **command, char ***envp)
{
	pid_t	pid;

	if (command && command[0])
	{
		if (is_builtin(command[0]) == true)
			g_status = execute_builtin(command, envp);
		else
		{
			if (!is_absolute(command[0]))
				get_cmd_path(*envp, &command[0], command[0]);
			if (access(command[0], X_OK) == -1)
			{
				g_status = 127;
				return (ft_error("Executable not found\n", false), 1);
			}
			pid = fork();
			if (pid == 0)
				execve(command[0], command, *envp);
			else
			{
				waitpid(pid, &g_status, 0);
				if (WIFEXITED(g_status))
					g_status = WEXITSTATUS(g_status);
			}
		}
	}
	return (0);
}
