#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}