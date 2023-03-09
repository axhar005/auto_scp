/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:20:45 by oboucher          #+#    #+#             */
/*   Updated: 2023/01/19 16:00:29 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	char	*new_str;
	size_t	start;
	size_t	end;

	if (!str || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	while (end > start && ft_strchr(set, str[end - 1]))
		end--;
	new_str = (char *)malloc((end - start) + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str + start, end - start + 1);
	return (new_str);
}
