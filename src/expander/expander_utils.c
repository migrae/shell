#include "../../include/minishell.h"

void	search_array(char **arr, char **env)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i] != NULL)
	{
		arr[i] = quote_cutter(arr[i]);
		arr[i] = look_for_dollar(arr[i], env);
		i++;
	}
}

char	*minimize_whitespace(char *str)
{
	char	**split;
	char	*out;

	if (!str)
		return (NULL);
	split = ft_split(str, ' ');
	if (!split)
		return (str);
	out = ft_strjoin_s_e(split, 0, ft_2darraylen(split), " ");
	ft_free2d(split);
	free (str);
	return (out);
}

char	*take_content(char *declaration)
{
	int		i;
	int		len;
	char	*content;

	content = NULL;
	len = 0;
	i = 0;
	while (declaration[i])
	{
		if (declaration[i] == '=')
		{
			len = ft_strlen(declaration + i + 1);
			content = ft_substr(declaration, i + 1, len);
			return (content);
		}
		i++;
	}
	return (NULL);
}

char	*search_var_in_env(char *var, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
			return (free(tmp), take_content(env[i]));
		i++;
	}
	return (free(tmp), NULL);
}

char	**if_split_contains_sentence(const char *dollar)
{
	char	**behind_dollar;
	int		i;
	int		n;

	i = 0;
	n = 0;
	behind_dollar = malloc(sizeof(char *) * 3);
	behind_dollar[2] = NULL;
	while (dollar[i])
	{
		if (dollar[0] == '?')
			break ;
		if ((!ft_isalpha(dollar[i])
				&& !ft_isalnum(dollar[i])) && dollar[i] != '_')
		{
			behind_dollar[0] = ft_substr(dollar, 0, i);
			behind_dollar[1] = ft_strdup(dollar + i);
			return (behind_dollar);
		}
		i++;
	}
	behind_dollar[n] = ft_strdup(dollar);
	behind_dollar[n + 1] = NULL;
	return (behind_dollar);
}
