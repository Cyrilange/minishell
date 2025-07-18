#include "miniutils.h"

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	return ;
}
