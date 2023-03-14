
#include "../../include/minishell.h"

t_token	*ft_new_token(char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = NULL;
	if (str)
		new_token->content = ft_strdup(str);
	new_token->next = NULL;
	new_token->type = content_analyse(new_token);
	return (new_token);
}

t_token	*ft_token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_token_add_back(t_token **tokens, t_token *new)
{
	t_token	*end;

	if (!new)
		return ;
	if (*tokens)
	{
		end = ft_token_last(*tokens);
		end->next = new;
	}
	else
		*tokens = new;
}

int	init_token(t_token **tokens, char *str)
{
	t_token	*temp;

	temp = NULL;
	temp = ft_new_token(str);
	if (!temp)
		return (1);
	ft_token_add_back(tokens, temp);
	return (0);
}

int load_tokens(char **split_tokens, t_data *data)
{
	int	i;

	i = 0;
	data->tokens = NULL;
	while(split_tokens[i])
	{
		if(init_token(&data->tokens, split_tokens[i]))
			return(ft_free2d(split_tokens), 0);
		i++;
	}
	if(split_tokens)
		ft_free2d(split_tokens);
	return (1);
}
