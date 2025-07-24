#include "../../includes/minishell.h"

char *expand_tilde(char *path, char **envp)
{
    char *home;
    char *result;
    int home_len, path_len;

    if (!path || path[0] != '~')
        return (ft_strdup(path));
    
    home = get_env_var_value("HOME", envp);
    if (!home)
        return (ft_strdup(path));
    
    if (path[1] == '\0')
        result = ft_strdup(home);
    else if (path[1] == '/')
    {
        home_len = ft_strlen(home);
        path_len = ft_strlen(path + 1);
        result = malloc(home_len + path_len + 1);
        if (!result)
        {
            free(home);
            return (ft_strdup(path));
        }
        ft_strcpy(result, home);
        ft_strcat(result, path + 1);
    }
    else
        result = ft_strdup(path);
    free(home);
    return (result);
}

void expand_tildes_in_tokens(t_token **tokens, char **envp)
{
    int i = 0;
    char *expanded;
    
    while (tokens[i])
    {
        if (tokens[i]->value && tokens[i]->value[0] == '~')
        {
            expanded = expand_tilde(tokens[i]->value, envp);
            free(tokens[i]->value);
            tokens[i]->value = expanded;
        }
        i++;
    }
}