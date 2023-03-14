#include "../../../include/minishell.h"

/* int is_outer(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
} */

void	ft_echo(t_exec *exec)
{
	char	*out;
	int		end;

	end = 0;
	while (exec->args[end])
		end++;
	if(!exec->args[1])
		exit(EXIT_FAILURE);
	if (ft_strncmp(exec->args[1], "-n", 3) == 0)
	{
		out = ft_strjoin_s_e(exec->args, 2, end - 1, " ");
		//out = quote_cutter(out);
		ft_putstr_fd(out, 1);
	}
	else
	{
		out = ft_strjoin_s_e(exec->args, 1, end - 1, " ");
		//out = quote_cutter(out);
		ft_putendl_fd(out, 1);
	}
	free(out);
}