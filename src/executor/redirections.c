#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

extern int g_status;

void redirect_outfile(char *fil, bool append)
{
	int outfile_fd;

	if (append == true)															  // if ">>"
		outfile_fd = open(fil, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR); // append
	else																		  // if ">"
		outfile_fd = open(fil, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);  // truncate
	dup2(outfile_fd, STDOUT_FILENO); // redirect stdout to the target file
	close(outfile_fd);
}

void redirect_infile(char *fil)
{
	int infile_fd;

	infile_fd = open(fil, O_RDONLY); // append
	dup2(infile_fd, STDIN_FILENO);	 // redirect stdout to the target file

	close(infile_fd);
}

bool is_path(char *command)
{
	int i = 0;
	if (command == NULL)
		return false;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return true;
		i++;
	}
	return false;
}

