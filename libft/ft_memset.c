#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	counter;

	counter = 0;
	while (counter < len)
		((char *)b)[counter++] = (unsigned char)c;
	return (b);
}
