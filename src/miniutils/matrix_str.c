#include "miniutils.h"
#include <stdio.h>

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

void	matrix_free(char ***matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[0] && matrix[0][i])
	{
		free(matrix[0][i]);
		i++;
	}
	if (matrix)
	{
		free(matrix[0]);
		*matrix = NULL;
	}
}

char	**matrix_str_dup(char **matrix, int replaceline, char *newstr)
{
	char	**newmatrix;
	int		len_matrix;
	int		i;
	int		j;

	j = 0;
	i = -1;
	len_matrix = matrix_len(matrix);
	newmatrix = malloc(sizeof(*newmatrix) * (len_matrix + 1));
	if (newmatrix == NULL)
		return (NULL);
	while (matrix[++i] != NULL)
	{
		if ( i == replaceline && newstr == NULL)
			continue;
		if (i == replaceline)
			newmatrix[j] = ft_strdup(newstr);
		else
			newmatrix[j] = ft_strdup(matrix[i]);
		if (newmatrix == NULL)
			return matrix_free(&newmatrix), NULL;
		j++;
	}
	newmatrix[i] = NULL;
	return (newmatrix);
}

char **matrix_str_add(char **matrix, char *newstr)
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
	while(matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}

}
