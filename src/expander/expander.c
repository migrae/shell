#include "../../include/minishell.h"

char	*look_for_dollar(char *str, char **env)
{
	int		i;
	char	*replaced_str;

	i = 0;
	if (!str || !str[0])
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			replaced_str = replace_string(str, env);
			if (!replaced_str)
				replaced_str = ft_strdup("");
			return (free(str), replaced_str);
		}
		i++;
	}
	return (str);
}

t_exec	*expand(t_exec *exec, char **env)
{
	char	**tmp_2d;
	char	**args;
	int		exp_cycle;

	if (var_in_str(exec->command) && ft_strncmp(exec->command, "echo", 5) != 0)
	{
		exp_cycle = 0;
		while (var_in_str(exec->command) && ++exp_cycle)
			exec->command = look_for_dollar(exec->command, env);
		tmp_2d = mini_lexer(exec->command);
		args = dupclicate_2d(exec->args);
		exec->args = replace_args(tmp_2d, args, exp_cycle);
		free(exec->command);
		exec->command = ft_strdup(exec->args[0]);
		ft_free2d(tmp_2d);
		ft_free2d(args);
	}
	return (exec);
}

t_exec	**expander(t_exec **exec, char **env, t_data *data)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->command && ft_strncmp(exec[i]->command, "echo", 5) != 0
			&& ft_strncmp(exec[i]->command, "/bin/echo", 10) != 0)
		{
			if (!go_through_exec(exec[i], env, data))
				return (NULL);
		}
		i++;
	}
	return (exec);
}
