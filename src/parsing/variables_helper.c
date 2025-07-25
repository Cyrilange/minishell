#include "../../includes/minishell.h"

char	*is_var_name(const char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i] && is_var_char(str[i]))
		i++;
	*len = i;
	if (i == 0 || (i == 1 && str[0] == '_'))
	{
		return (NULL);
	}
	return (ft_strndup(str, i));
}

char *append_str(char *base, const char *add)
{
	char	*new_str;
	size_t	base_len;
	size_t	add_len;

	if (!add)
		return (base);
	if (!base)
		return (ft_strdup(add));
	base_len = ft_strlen(base);
	add_len = ft_strlen(add);
	new_str = malloc(base_len + add_len + 1);
	if (!new_str)
	{
		free(base);
		return (NULL);
	}
	ft_strcpy(new_str, base);
	ft_strcat(new_str, add);
	free(base);
	return (new_str);
}

