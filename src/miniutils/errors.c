#include  "miniutils.h"

void	ft_error(char *str, bool exit_program)
{
	int	i;

	i = 0;
	write(2, "Error: ", 8);
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	if (exit_program == true)
		exit(1);
}
