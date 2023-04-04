#include "../../../include/minishell.h"

int	built_in(t_exec *exec, char ***env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0
		|| ft_strncmp(exec->command, "/bin/echo", 10) == 0)
		return (g_errno = ft_echo(exec, data), 1);
	else if (ft_strncmp(exec->command, "cd", 3) == 0)
		return (g_errno = ft_cd(exec, env), 1);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
		return (g_errno = ft_pwd(), 1);
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		return (g_errno = ft_export(exec->args, &data->env), 1);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
		return (g_errno = ft_unset(exec->args, &data->env), 1);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
		return (g_errno = ft_env(data->env), 1);
	else if (ft_strncmp(exec->command, "exit", 5) == 0)
		return (g_errno = ft_exit(exec->args), 1);
	return (0);
}

int	built_in_child(t_exec *exec, char ***env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0
		|| ft_strncmp(exec->command, "/bin/echo", 10) == 0)
		return (g_errno = ft_echo(exec, data), free_data(data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "cd", 3) == 0)
		return (g_errno = ft_cd(exec, env), free_data(data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
		return (g_errno = ft_pwd(), free_data(data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		return (g_errno = ft_export(exec->args, &data->env), free_data(data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
		return (g_errno = ft_unset(exec->args, &data->env), free_data(data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
		return (g_errno = ft_env(data->env), free_data(data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "exit", 5) == 0)
		return (g_errno = ft_exit(exec->args), free_data(data), exit(g_errno), 1);
	return (0);
}
