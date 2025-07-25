#include "../../includes/minishell.h"
#include <stdlib.h>

extern int g_status;

static char *process_special_variable(int *i, char *result)
{
    char *status_str;
    char *tmp_res;

    status_str = ft_itoa(g_status);
    if (!status_str)
    {
        free(result);
        return (NULL);
    }
    tmp_res = append_str(result, status_str);
    free(status_str);

    if (!tmp_res)
        return (NULL);
    (*i)++;
    return (tmp_res);
}

static char *process_variable_name(const char *str, int *i, char *result, char **envp)
{
    int  len;
    char *var_name;
    char *value;
    char *tmp_res;

    len = 0;
    var_name = is_var_name(&str[*i], &len);
    if (!var_name)
    {
        return (result);
    }

    value = get_env_var_value(var_name, envp);
    free(var_name);

    if (!value)
    {
        value = ft_strdup("");
        if (!value)
        {
            free(result);
            return (NULL);
        }
    }

    tmp_res = append_str(result, value);
    free(value);
    
    if (!tmp_res)
    {
        return (NULL);
    }
    result = tmp_res;
    *i += len;
    
    return (result);
}


static char *process_dollar(const char *str, int *i, char *result, char **envp)
{
    char *tmp_res = NULL;

    (*i)++;
    if (str[*i] == '?')
        tmp_res = process_special_variable(i, result);
    else if (isalpha(str[*i]) || str[*i] == '_')
        tmp_res = process_variable_name(str, i, result, envp);
    else
    {
        tmp_res = append_str(result, "$");
    }
    
    if (!tmp_res)
        return (NULL);
    return (tmp_res);
}

static char *process_normal_char(char c, char *result)
{
    char tmp[2];
    char *r;

    tmp[0] = c;
    tmp[1] = 0;
    return (append_str(result, tmp));
}

char *expand_variables(const char *str, t_quotes quote_type, char **envp)
{
    int   i;
    char *result;
    char *tmp_res;

    i = 0;
    if (quote_type == SINGLE_QUOTE)
        return (ft_strdup(str));

    result = ft_strdup("");
    if (!result) return (NULL);

    while (str[i])
    {
        if (str[i] == '$' && quote_type != SINGLE_QUOTE)
        {
            tmp_res = process_dollar(str, &i, result, envp);
        }
        else
        {
            tmp_res = process_normal_char(str[i], result);
            i++;
        }

        if (!tmp_res)
        {
			free(result);
            return (NULL);
        }
        result = tmp_res;
    }
    return (result);
}