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

void	fill_red_pos(t_cmd *cmd)
{
	t_token *red;
	int		i;

	i = 1;
	if (cmd->arg != NULL)
		cmd->builtin = check_builtin(cmd->arg[0]);
	else
		cmd->builtin = 0;
	red = cmd->redirection;
	if (red == NULL)
		return;
	while (red)
	{
		red->pos = i;
		red = red->next;
		i++;
	}
	return;
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
		fill_red_pos(temp);
		if (i == 0)
			temp->pipe_in = 0;
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