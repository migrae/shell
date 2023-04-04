#include "../../include/minishell.h"

char	*ft_replace_var(char **env, char *dollar)
{
	char	**behind_dollar;
	char	*value;

	value = NULL;
	if (!dollar)
		return (value);
	if (keep_dollar(dollar) == 1)
		return (dollar - 1);
	behind_dollar = if_split_contains_sentence(dollar);
	if (ft_strncmp(behind_dollar[0], "?", 1) == 0)
	{
		value = ft_itoa(g_errno);
		if (ft_strlen(behind_dollar[0]) > 1)
			value = ft_strjoin_free_opt(value, behind_dollar[0] + 1, 1, 0);
	}
	else
		value = search_var_in_env(behind_dollar[0], env);
	value = ft_strjoin_free_opt(value, behind_dollar[1], 1, 0);
	ft_free2d(behind_dollar);
	free(dollar - 1);
	return (value);
}

/* char	*rplc_fnlstring(char *finalstring, char *substr, char **env, int flag)
{
	char	*tmp;

	tmp = substr;
	look_for_singlequote(finalstring, &flag);
	if (flag == 0)
		substr = ft_replace_var(env, substr + 1);
	finalstring = ft_strjoin_free_opt(finalstring, substr, 1, 1);
	free(tmp);
	return (finalstring);
} */

char	*replace_string(char *s, char **env)
{
	char	*finalstring;
	char	*substr;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i] && s[i] != '$')
		i++;
	finalstring = ft_substr(s, 0, i);
	while (s[i])
	{
		if (s[i] == '$')
		{
			substr = ft_substr(s, i, ft_length_dollar(s + i, '$'));
			look_for_singlequote(finalstring, &flag);
			if (flag == 0)
				substr = ft_replace_var(env, substr + 1);
			finalstring = ft_strjoin_free_opt(finalstring, substr, 1, 1);
		}
		i++;
	}
	if (!is_inquotes(finalstring))
		finalstring = minimize_whitespace(finalstring);
	return (finalstring);
}
