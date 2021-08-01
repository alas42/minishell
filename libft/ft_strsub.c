#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*fresh;
	unsigned int	i;

	fresh = NULL;
	i = 0;
	if (s == NULL)
		return (fresh);
	fresh = (char *)malloc(sizeof(char) * (len + 1));
	if (!(fresh))
		return (NULL);
	while (i < len)
		fresh[i++] = s[start++];
	fresh[i] = '\0';
	return (fresh);
}
