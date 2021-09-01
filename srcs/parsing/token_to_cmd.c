#include "../includes/minishell.h"

void	*cmnd_init(void)
{
	t_cmnd 	*cmd;

	cmd = (t_cmnd *)malloc(sizeof(t_cmnd));
	if (cmd == NULL)
		return (NULL);
	cmd->redirection = NULL;
	cmd->arg = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	*merge_content(char *str, char *content)
{
	char	*temp;

	temp = NULL;
	if (str)
	{
   		temp = ft_strdup(str);
		free(str);
	}
	str = ft_strjoin(temp, content);
	if (temp)
		free(temp);
	temp = ft_strdup(str);
	free(str);
	str = ft_strjoin(temp, " ");
	free(temp);
	return (str);
}

void	red_lst_add_back(t_cmnd *cmd, t_token *new)
{
	t_token	*ls;
	if (new == NULL)
		return ;
	if (cmd->redirection)
		ls = cmd->redirection;
	else
	{
		cmd->redirection = new;
		return ;
	}
	while (ls->next != NULL)
		ls = ls->next;
	new->prev = ls;
	ls->next = new;
}

void	cmd_lst_add_back(t_cmnd *cmd, t_infos *info)
{
	t_cmnd *ls;

	if (cmd == NULL)
		return;
	if (info->commands)
		ls = info->commands;
	else
	{
		info->commands = cmd;
		return;
	}
	while(ls->next)
		ls = ls->next;
	ls->next = cmd;
}

void	move_to_cmd(t_infos *info)
{
	t_token *token;
	t_token *new;
	t_cmnd	*cmd;
	char	*str;

	cmd = cmnd_init();
	if (cmd == NULL)
		printf("error in cmd init return \n");
	str = NULL;
	new = NULL;
	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "pipe")))
		{
			//I add the cmd in link_list
			//I update the token

			printf("str in the end - [%s]\n", str);
			cmd->arg = ft_split_char(str, ' ');
			cmd_lst_add_back(cmd, info);
			cmd = NULL;
			cmd = cmnd_init();
			str = NULL;
			printf("--------------\n");
		}
		if (!(ft_strcmp(token->type, "literal")))
			str = merge_content(str, token->content);
		else
		{
			new = token_init();
			new->content = ft_strdup(token->content);
			new->type = ft_strdup(token->type);
			red_lst_add_back(cmd, new);
		}
		//printf("token content [%s]\n", token->content);
		token = token->next;
	}
	print_cmnds(info);
}

