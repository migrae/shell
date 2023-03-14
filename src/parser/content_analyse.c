#include "../../include/minishell.h"

int	ft_islower(int c)
{
	if ((c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

int is_option(char *str)
{
	int	i;

	i = 0;
	if(str[i] == '"' || str[i] == '\'')
		i++;
	if (str[i] != '-')
		return (0);
	else
		i++;
	if (!ft_islower(str[i]))
		return (0);
	while (ft_islower(str[i]))
		i++;
	if(str[i] == '"' || str[i] == '\'')
		return (1);
	else
		return (0);
}

t_tokentype	content_analyse(t_token *token)
{
	if(token->content)
	{
		if (token->content[0] == '<' || token->content[0] == '>')
			return(redirection);
		else if (token->content[0] == '|')
			return(is_pipe);
		else
			return(word);	
	}
	return(empty);
}