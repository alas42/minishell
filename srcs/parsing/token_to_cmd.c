#include "../includes/minishell.h"

void	fill_redirections(t_token *tokens, t_cmd *cmd, t_infos *info)
{
	t_token	*temp;

	temp = token_init();
	if (temp == NULL)
		print_error(E_MALLOC, info);
	temp->content = ft_strdup(tokens->content);
	temp->type = ft_strdup(tokens->type);
	red_lst_add_back(cmd, temp);
	temp = NULL;
}

int	get_cmd_args_num(t_infos *info, int start, int end)
{
	t_token	*tokens;
	int		i;
	int		counter;

	tokens = info->tokens;
	i = -1;
	counter = 0;
	while (++i < start)
		tokens = tokens->next;
	while (i++ <= end && tokens != NULL)
	{
		if (!(ft_strcmp(tokens->type, "literal")))
			counter++;
		tokens = tokens->next;
	}
	return (counter);
}

char	**get_cmd_args(t_infos *info, int start, int end)
{
	t_token	*tokens;
	int		i;
	int		counter;
	char	**args;
	int		j;

	i = -1;
	j = 0;
	tokens = info->tokens;
	counter = get_cmd_args_num(info, start, end);
	args = (char **)malloc(sizeof(char *) * (counter + 1));
	if (args == NULL)
		print_error(E_MALLOC, info);
	while (++i < start)
		tokens = tokens->next;
	while (i++ <= end && tokens != NULL)
	{
		if (!(ft_strcmp(tokens->type, "literal")))
			args[j++] = ft_strdup(tokens->content);
		tokens = tokens->next;
	}
	args[j] = NULL;
	return (args);
}

void	fill_cmd(t_infos *info, int start, int end, t_cmd *cmd)
{
	int		i;
	t_token	*tokens;

	i = -1;
	if (start < 0 || start > ft_lstlast_token(info->tokens)->pos
		|| start > end || end < 0 || end > ft_lstlast_token(info->tokens)->pos)
	{
		free(cmd);
		return ;
	}
	tokens = info->tokens;
	while (++i < start)
		tokens = tokens->next;
	cmd->arg = get_cmd_args(info, start, end);
	while (i++ <= end && tokens != NULL)
	{
		if ((ft_strcmp(tokens->type, "literal")))
			fill_redirections(tokens, cmd, info);
		tokens = tokens->next;
	}
	cmd_lst_add_back(cmd, info);
}

void	move_to_cmd(t_infos *info)
{
	t_token	*token;
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
				print_error(E_MALLOC, info);
			fill_cmd(info, start, token->pos - 1, cmd);
			start = token->pos + 1;
			cmd = NULL;
		}
		token = token->next;
	}
	cmd = cmnd_init();
	if (cmd == NULL)
		print_error(E_MALLOC, info);
	fill_cmd(info, start, ft_lstlast_token(info->tokens)->pos, cmd);
	fill_cmd_info(info);
}
