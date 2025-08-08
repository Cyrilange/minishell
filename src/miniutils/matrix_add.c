#include "miniutils.h"

char	**matrix_str_add(char **matrix, char *newstr)
{
	char	**newmatrix;
	int		len;
	int		i;

	i = -1;
	newmatrix = NULL;
	if (!newstr)
		return (matrix);
	len = matrix_len(matrix);
	newmatrix = malloc(sizeof(char *) * (len + 2));
	newmatrix[len + 1] = NULL;
	if (!newmatrix)
		return (matrix);
	while (++i < len)
	{
		newmatrix[i] = ft_strdup(matrix[i]);
		if (!newmatrix[i])
		{
			matrix_free(&matrix);
			matrix_free(&newmatrix);
		}
	}
	newmatrix[i] = ft_strdup(newstr);
	matrix_free(&matrix);
	return (newmatrix);
}

void	matrix_str_print(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}
