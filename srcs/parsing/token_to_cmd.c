#include "../includes/minishell.h"

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
	char	*join_str;

	i = -1;
	counter = 0;
	tokens = info->tokens;
	join_str = ft_strdup("");
	while(++i < start)
		tokens = tokens->next;
	while(i++ <= end && tokens != NULL)
	{
		if (!(ft_strcmp(tokens->type, "literal")))
		{
			join_str = merge_content(join_str, tokens->content, 1);
			counter++;
		}
		tokens = tokens->next;
	}
	join_str[ft_strlen(join_str) - 1] = '\0';
	args = ft_split(join_str, ' ');
	free(join_str);
	return (args);
}

void	fill_cmd(t_infos *info, int start, int end, t_cmd *cmd)
{
	int		i;
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
	while (i++ <= end && tokens != NULL)
	{
		if ((ft_strcmp(tokens->type, "literal")))
			fill_redirections(tokens, cmd);
		tokens = tokens->next;
	}
	cmd_lst_add_back(cmd, info);
}

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
