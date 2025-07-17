#include "../../includes/minishell.h"

void update_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("PWD", cwd, 1);
    }
    else
    {
        perror("getcwd");
    }
}

int builtin_pwd(void)
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
        return (0);
    }
    return (1);
}
