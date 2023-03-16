#include "scp.h"

char	**ft_dfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

size_t isfolder(char *str)
{

    size_t i = ft_strlen(str);
    while (i-- >= ft_strlen(str)-4)
    {
        if (str[i] == '.')
            return(0);
    }
    return(1);
}

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

char	*ft_null_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	s1_len = ft_gnl_strlen(s1);
	s2_len = ft_gnl_strlen(s2);
	new = ft_gnl_calloc(s1_len + s2_len + 1, sizeof(char));
	if (new == NULL)
		return (new = ft_sfree(new));
	while (s1_len + s2_len-- > s1_len)
		new[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		new[s1_len] = s1[s1_len];
	if (*new == 0)
		new = ft_sfree(new);
	return (new);
}