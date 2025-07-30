#include "../includes/minishell.h"

extern int g_status;

bool it_is_path(const char *cmd)
{
    if (!cmd)
        return false;
    // Si la commande contient au moins un '/', c'est un chemin
    if (strchr(cmd, '/'))
        return true;
    return false;
}

int execute_command(char **command, char ***envp)
{
    char *save_cmd_name;
    char *resolved_path = NULL;
    bool should_free = false;
    pid_t pid;

    if (!command || !command[0])
        return (1);

    save_cmd_name = command[0];
    if (is_builtin(command[0]) == true)
    {
        g_status = execute_builtin(command, envp);
        return (0);
    }

    if (!it_is_path(command[0]))
    {
        get_cmd_path(*envp, &resolved_path, command[0]);
        should_free = true;
    }
    else
    {
        resolved_path = command[0];
    }

    if (!resolved_path || access(resolved_path, X_OK) == -1)
    {
        g_status = 127;
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(save_cmd_name, 2);
        ft_putstr_fd(": command not found\n", 2);
        if (should_free)
            free(resolved_path);
        return (1);
    }

    pid = fork();
    if (pid == 0)
    {
        execve(resolved_path, command, *envp);
        ft_putstr_fd("execve", 2);
        if (should_free)
            free(resolved_path);
        exit(1);
    }
    else if (pid > 0)
    {
        waitpid(pid, &g_status, 0);
        g_status = g_status / 256;
        if (should_free)
            free(resolved_path);
    }
    else
    {
        if (should_free)
            free(resolved_path);
        return (1);
    }

    return (0);
}
