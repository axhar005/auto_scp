/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:28:18 by oboucher          #+#    #+#             */
/*   Updated: 2023/01/17 16:48:40 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	temp;

	src_len = ft_strlen(src);
	if (destsize == 0)
		return (src_len);
	if (!dest)
		return (0);
	if (src_len < destsize)
	{
		temp = src_len;
	}
	else
	{
		temp = destsize - 1;
	}
	ft_memcpy(dest, src, temp);
	dest[temp] = '\0';
	return (src_len);
}
