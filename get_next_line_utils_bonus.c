#include "get_next_line_bonus.h"

size_t	ft_strlen_bonus(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_bonus(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*result;

	i = -1;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len1 = ft_strlen_bonus(s1);
	len2 = ft_strlen_bonus(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[++i])
		result[i] = s1[i];
	i = -1;
	while (s2[++i])
		result[len1 + i] = s2[i];
	result[len1 + i] = '\0';
	return (free(s1), result);
}
