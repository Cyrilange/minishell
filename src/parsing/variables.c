#include "../includes/minishell.h"

static int    is_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}


static char *is_var_name(const char *str, int *len)
{
	int i;

	i = 0;
	while (str[i] && is_var_char(str[i]))
		i++;
	*len = i;
	return ft_strndup(str, i);
}

static char *append_str(char *base, const char *add)
{
    if (!base)
        return strdup(add);
    char *new_str = malloc(ft_strlen(base) + ft_strlen(add) + 1);
    if (!new_str)
    {
        free(base);
        return NULL;
    }
    ft_strcpy(new_str, base);
    ft_strcat(new_str, add);
    free(base);
    return new_str;
}

char *expand_variables(const char *str, t_quotes quote_type)
{
    if (quote_type == SINGLE_QUOTE)
        return ft_strdup(str);

    char *result = ft_strdup("");
    if (!result)
        return NULL;

    int i = 0;
    while (str[i])
    {
        if (str[i] == '$' && quote_type != SINGLE_QUOTE)
        {
            i++;
            if (str[i] == '?')
            {
                result = append_str(result, "0");
                i++;
            }
            else if (isalpha(str[i]) || str[i] == '_')
            {
                int len = 0;
                char *var_name = is_var_name(&str[i], &len);
                char *value = getenv(var_name);
                free(var_name);
                if (!value)
                    value = "";
                result = append_str(result, value);
                i += len;  
            }
            else
                result = append_str(result, "$");
        }
        else
        {
            char tmp[2] = {str[i], 0};
            result = append_str(result, tmp);
            i++;
        }
        if (!result)
            return NULL;
    }
    return result;
}
