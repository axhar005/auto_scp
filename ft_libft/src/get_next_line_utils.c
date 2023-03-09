/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:09:06 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/08 01:10:52 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_gnl_bzero(void *b, size_t len)
{
	while (len--)
		((char *)b)[len] = 0;
}

void	*ft_sfree(void *str)
{
	if (str)
		free(str);
	return (NULL);
}

void	*ft_gnl_calloc(size_t count, size_t size)
{
	void	*new;

	new = malloc(count * size);
	if (!new)
		return (new = ft_sfree(new));
	ft_gnl_bzero(new, count * size);
	return (new);
}

size_t	ft_gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
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
	return (ft_sfree(s1), new);
}
