#include "../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	c1 = (unsigned char)*s1;
	c2 = (unsigned char)*s2;
	while (*s1 && *s2)
	{
		if (c1 != c2)
			return (c1 - c2);
		++s1;
		++s2;
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
	}
	return (c1 - c2);
}
