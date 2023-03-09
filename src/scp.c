#include "scp.h"

size_t	ft_strcnum(char *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == c)
			len++;
		i++;
	}
	return (len);
}

char	*ft_strschr(char *str, char c)
{
	size_t i = 0;
	size_t j = 0;
	size_t len;
	size_t chrnum;
	char *new;
    char *temp = str;

	chrnum = ft_strcnum(str, c);
	len = ft_strlen(str);
	new = ft_calloc(len - chrnum + 1, sizeof(char));
	if (chrnum > 0)
	{
		while (str[i])
		{
			if (str[i] != c)
			{
				new[j] = str[i];
				j++;
			}
			i++;
		}
		ft_sfree(temp);
		return (new);
	}
	return (str);
}