#ifndef MINIUTILS_H
#define MINIUTILS_H

#include <stdbool.h>
#include "../../includes/libft/libft.h"

// matrix
char **matrix_str_add(char **matrix, char *newstr);
char **matrix_str_dup(char **matrix, int replaceline, char *newstr);
void matrix_str_print(char **matrix);
int matrix_len(char **matrix);
void	matrix_free(char ***matrix);

// errors
void	ft_error(char *str, bool exit_program);

#endif // MINIUTILS_H
