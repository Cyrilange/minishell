#include "../includes/minishell.h"

extern int g_status;

bool it_is_path(const char *cmd)
{
	if (!cmd)
		return false;
	if (strchr(cmd, '/'))
		return true;
	return false;
}

static int helper_exec_xmd_path(char **resolved_path, char *save_cmd_name, bool should_free)
{
	g_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(save_cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (should_free && *resolved_path)
		free(*resolved_path);
	return (1);
}


static int helper_handle_builtin(char **command, char ***envp)
{
	if (!command || !command[0])
		return (1);
	if (is_builtin(command[0]) == true)
	{
		g_status = execute_builtin(command, envp);
		return (0);
	}
	return -1;
}

static char *helper_resolve_path(char *cmd, char **envp, bool *should_free)
{
	char *resolved_path = NULL;

	if (!it_is_path(cmd))
	{
		get_cmd_path(envp, &resolved_path, cmd);
		*should_free = true;
	}
	else
	{
		resolved_path = cmd;
		*should_free = false;
	}
	return resolved_path;
}

static int helper_exec_process(char *resolved_path, char **command, char **envp, bool should_free)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(resolved_path, command, envp);
		ft_putstr_fd("execve", 2);
		if (should_free)
			free(resolved_path);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &g_status, 0);
		g_status = g_status / 256;
	}
	else
	{
		if (should_free)
			free(resolved_path);
		return (1);
	}
	if (should_free)
		free(resolved_path);
	return (0);
}

int execute_command(char **command, char ***envp)
{
	char *save_cmd_name;
	char *resolved_path;
	bool should_free = false;
	int builtin_result;

	builtin_result = helper_handle_builtin(command, envp);
	if (builtin_result != -1)
		return (builtin_result);

	save_cmd_name = command[0];
	resolved_path = helper_resolve_path(command[0], *envp, &should_free);

	if (!resolved_path || access(resolved_path, X_OK) == -1)
	{
		helper_exec_xmd_path(&resolved_path, save_cmd_name, should_free);
		return (1);
	}
	return helper_exec_process(resolved_path, command, *envp, should_free);
}

 /*

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
		resolved_path = command[0];
	if (!resolved_path || access(resolved_path, X_OK) == -1)
	{
		helper_exec_xmd_path(&resolved_path, save_cmd_name, should_free);
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
*/