#include "../include/minishell.h"

int	do_shit(char **split, char *str, int *i, int *start)
{
	if (is_delimiter(str[*i]))
	{
		split = makestring(split, str, *start, *i);
		while (ft_iswhitespace(str[*i]))
			(*i)++;
		*start = *i;
		if (jump_redir(str, i))
			split = makestring(split, str, *start, *i);
		while (ft_iswhitespace(str[*i]))
			(*i)++;
		*start = *i;
		return (1);
	}
	return (0);
}

char	**create_strings(char **split, char *str)
{
	int	i;
	int	flag;
	int	keep_quote;
	int	start;
	int	is_split;

	i = 0;
	start = 0;
	flag = 0;
	keep_quote = 0;
	is_split = 0;
	//printf("create\n");
	jump_delimiter_split(split, str, &start, &i);
	while (str[i])
	{
		handle_quote(str, &i, &flag, &keep_quote);
		if (flag == 0 || flag == 3)
			is_split = do_shit(split, str, &i, &start);
		if (is_split && flag == 3)
			flag = 4;
		if (str[i] && !handle_quote(str, &i, &flag, &keep_quote))
			i++;
	}
	split = makestring(split, str, start, i);
	return (split);
}

int	countstrs(char *str)
{
	int	i;
	int	count;
	int	n;
	int	flag;
	int	keep_quote;

	i = 0;
	count = 0;
	n = 0;
	flag = 0;
	keep_quote = 0;
	while (str[i])
	{
		handle_quote(str, &i, &flag, &keep_quote);
		if (flag == 0 || flag == 3)
		{
			n = jump_delimiters(str, &i);
			count += n;
			if (n)
			{
				if (flag == 3)
					flag = 4;
				i--;
			}
		}
		if (str[i] && !handle_quote(str, &i, &flag, &keep_quote))
			i++;
	}
	return (count);
}

char	**lexer(char *str)
{
	char	**split;
	int		strnumber;

	split = NULL;
	str = ft_strtrim(str, "\n\t\v\f\r ");
	strnumber = countstrs(str) + 1;
	split = allocate(split, strnumber);
	create_strings(split, str);
	split[strnumber] = NULL;
	free(str);
	ft_put2dstr_fd(split, 2);
	return (split);
}
