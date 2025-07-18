#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
# include <sys/stat.h>

extern int g_status;

void	redirect_outfile(char *fil, bool append)
{
	int	outfile_fd;

    if (append == true) // if ">>"
        outfile_fd = open(fil, O_WRONLY | O_APPEND| O_CREAT, S_IRUSR | S_IWUSR); // append
    else // if ">"
        outfile_fd = open(fil, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR); // truncate
    dup2(outfile_fd, STDOUT_FILENO); // redirect stdout to the target file
	close(outfile_fd);
}


void	redirect_infile(char *fil)
{
	int	infile_fd;

    infile_fd = open(fil, O_RDONLY); // append
    dup2(infile_fd, STDIN_FILENO); // redirect stdout to the target file
    
	close(infile_fd);
}

bool is_absolute(char *command)
{
	if (command[0] == '/')
		return true;
    return false;
}

int execute_command(char **command, char ***envp)
{
        if (command && command[0])// Execute command
        {
            if (is_builtin(command[0]) == true) // if its a builtin
                g_status = execute_builtin(command, envp);
            else // if its not a builtin
			{
                if (!is_absolute(command[0])) // if program was not sent as an abs path
                    get_cmd_path(*envp, &command[0], command[0]); // convert program name to abs path for execve
				if (access(command[0], X_OK) == -1) // if path cant be executed
				{
        		            g_status = 127;
				    ft_putstr_fd("minishell: ", 2);
				    ft_putstr_fd(command[0], 2);
		                    return (ft_putstr_fd(": command not found\n", 2), 1); // throw error
				}
                pid_t pid = fork(); // create a child proc
				if (pid == 0) // child proc
                    execve(command[0], command, *envp);
				else // parent proc
				{
                    waitpid(pid, &g_status, 0);
                    g_status = g_status / 256; // idk why waitpid multiplies the errcode by 256
				}
			}
        }
}
