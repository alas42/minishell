#include "../includes/minishell.h"

//Remove the first and last char from content '' ""
char    *update_quotes_content(t_token *temp)
{
	char    *str;
	int     len;
	int     i;
	i = 0;

	len = ft_strlen(temp->content);
	str = (char *)malloc(sizeof(char) * len);
	while(i < len - 2)
	{
		str[i] = temp->content[i+1];
		i++;
	}
	str[i] = '\0';
	free(temp->content);
	return(str);
}

int     check_dollar(char *content)
{
	int     i;
	int     len;

	i = 0;
	len = ft_strlen(content);
	while (i < len)
	{
		if (content[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

//Update the type of token
void    update_token_type(t_infos *info, char *from, char *to)
{
	t_token *temp;
	int     i;

	i = -1;
	temp = info->tokens;
	while (temp)
	{
		if (!(ft_strcmp(temp->type, from)))
		{
			if (!(ft_strcmp(temp->type, "double_quote")))
				i = check_dollar(temp->content);
			free(temp->type);
			if (i != 1)
				temp->type = ft_strdup(to);
			else
				temp->type = ft_strdup("literal_dollar");
			temp->content = update_quotes_content(temp);
			break;
		}
		temp = temp->next;
	}
}

