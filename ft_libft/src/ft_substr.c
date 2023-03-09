/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:40:22 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/09 00:58:36 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	str_len;

	str_len = ft_strlen(str);
	if (!str)
		return (NULL);
	if (start > str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = (str_len - start);
	new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, str + start, len);
	return (new);
}
