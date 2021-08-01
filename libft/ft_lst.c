#include "../includes/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
	{
		*alst = new;
	}
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

int	ft_lstsize(t_list *lst)
{
	t_list	*pos;
	int		id_pos;

	id_pos = 0;
	pos = lst;
	while (pos != NULL)
	{
		pos = pos->next;
		id_pos++;
	}
	return (id_pos);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!(new))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
