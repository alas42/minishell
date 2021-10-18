#include "../includes/minishell.h"

char	*merge_content(char *str, char *content, int space)
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
	if (space == 1)
	{
		temp = ft_strdup(str);
		free(str);
		str = ft_strjoin(temp, " ");
		free(temp);
	}
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

char	**get_cmd_args(t_infos *info, int start, int end)
{
	int		i;
	t_token	*tokens;
	int		counter;
	char	**args;

	i = -1;
	counter = 0;
	tokens = info->tokens;
	while(++i < start)
		tokens = tokens->next;
	while(i++ <= end && tokens != NULL)
	{
		if (!(ft_strcmp(tokens->type, "literal")))
			counter++;
	}
	args = NULL;
	args = (char **)malloc(sizeof(char *) * (counter + 1));
	if (args == NULL)
		printf("Error in malloc in get_cmd_args\n");
	return (args);
}

void	fill_cmd(t_infos *info, int start, int end, t_cmd *cmd)
{
	int		i;
	int		j;
	t_token *tokens;

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
	cmd->arg = get_cmd_args(info, start, end);
	j = 0;
	while (i++ <= end && tokens != NULL)
	{
		if (!(ft_strcmp(tokens->type, "literal")))
		{
			cmd->arg[j] = ft_strdup(tokens->content);
			j++;
		}
		else
			fill_redirections(tokens, cmd);
		tokens = tokens->next;
	}
	cmd->arg[j] = NULL;
	cmd_lst_add_back(cmd, info);
}

int		check_builtin(char *str)
{
	if (str == NULL)
		return (0);
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
			info->nb_pipe = info->nb_pipe + 1;
		}
		else
			temp->pipe_out = 0;
		temp = temp->next;
		i++;
	}
	info->nb_cmd = i;	
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
