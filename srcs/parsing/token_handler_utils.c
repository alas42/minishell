#include "../includes/minishell.h"

void	free_doub_char(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

char	*ft_strndup(char *s1, size_t length)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc((length + 1) * sizeof(char));
	p[length] = '\0';
	if (p == 0)
		return (NULL);
	else
	{
		while (i < length)
		{
			p[i] = s1[i];
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}

void	fill_result(char **result, char *str, int chunk, char c)
{
	int		i;
	size_t	len;

	i = 0;
	while (i < chunk)
	{
		len = 0;
		while (str[len] != c && str[len] != '\0')
			len++;
		result[i] = ft_strndup(str, len);
		str = str + len + 1;
		i++;
	}
	result[i] = NULL;
}

char	**ft_split(char *str, char c)
{
	char	**result;
	int		chunk;
	int		i;

	i = -1;
	if (str == NULL)
		return (NULL);
	chunk = 1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			chunk++;
	}
	result = (char **)malloc(sizeof(char *) * (chunk + 1));
	fill_result(result, str, chunk, c);
	return (result);
}
