#include "../includes/minishell.h"

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

void	fill_redirections(t_token *tokens, t_cmd *cmd)
{
	t_token *temp;

	temp = token_init();
	if (temp == NULL)
		printf("initialization error in token (redirection cmnd)\n");
	temp->content = ft_strdup(tokens->content);
	temp->type = ft_strdup(tokens->type);
	red_lst_add_back(cmd, temp);
	temp = NULL;
}

void	fill_cmd(t_infos *info, int start, int end, t_cmd *cmd)
{
	int		i;
	t_token *tokens;
	char	*str;

	i = -1;
	if (start < 0 || start > ft_lstlast_token(info->tokens)->pos
	|| start > end || end < 0 || end > ft_lstlast_token(info->tokens)->pos)
	{
		free(cmd);
		return;
	}
	tokens = info->tokens;
	while (++i < start)
		tokens = tokens->next;
	str = NULL;
	while (i++ <= end && tokens != NULL)
	{
		if (!(ft_strcmp(tokens->type, "literal")))
			str = merge_content(str, tokens->content);
		else
			fill_redirections(tokens, cmd);
		tokens = tokens->next;
	}
	i = ft_strlen(str);
	str[i - 1] = '\0';
	cmd->arg = ft_split(str, ' ');
	cmd_lst_add_back(cmd, info);
	free(str);
}

int		check_builtin(char *str)
{
	if (!(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "echo"))
		|| !(ft_strcmp(str, "cd")) || !(ft_strcmp(str, "env"))
		|| !(ft_strcmp(str, "exit")) || !(ft_strcmp(str, "export"))
		|| !(ft_strcmp(str, "pwd")))
		return (1);
	return (0);
}

void	fill_cmd_info(t_infos *info)
{
	t_cmd *temp;
	int		i;

	i = 0;
	temp = info->commands;
	while(temp)
	{
		temp->index = i;
		if (temp->arg != NULL)
			temp->builtin = check_builtin(temp->arg[0]);
		else
			temp->builtin = 0;
		if (i == 0)
		{
			temp->pipe_in = 0;
		}
		if (temp->next != NULL)
		{
			temp->pipe_out = 1;
			temp->next->pipe_in = 1;
		}
		else
			temp->pipe_out = 0;
		temp = temp->next;
		i++;
	}
	
}
//above ft_split_char divides everything with space as a deliminator. echo "hello world" -> [echo, hello, world] should be ->[echo , hello world]
void	move_to_cmd(t_infos *info)
{
	t_token *token;
	int		start;
	t_cmd	*cmd;

	start = 0;
	token = info->tokens;
	while (token)
	{
		if (!(ft_strcmp(token->type, "pipe")))
		{
			cmd = cmnd_init();
			if (cmd == NULL)
				printf("error in cmd init return \n");
			fill_cmd(info, start, token->pos - 1, cmd);
			start = token->pos + 1;
			cmd = NULL;
		}
		token = token->next;
	}
	cmd = cmnd_init();
	if (cmd == NULL)
		printf("error in cmd init return \n");
	fill_cmd(info, start, ft_lstlast_token(info->tokens)->pos, cmd);
	fill_cmd_info(info);
}
