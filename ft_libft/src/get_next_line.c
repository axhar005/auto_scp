/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:09:03 by oboucher          #+#    #+#             */
/*   Updated: 2023/03/08 16:40:31 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_find(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_small_split(char *line, size_t *pos)
{
	char	*fnext_line;
	size_t	i;

	i = 0;
	while (line[i])
		if (line[i++] == '\n')
			break ;
	*pos = i;
	fnext_line = ft_gnl_calloc(i + 1, sizeof(char));
	if (!fnext_line)
		return (ft_sfree(fnext_line));
	while (i--)
		fnext_line[i] = line[i];
	return (fnext_line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	t_var		var;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX
		|| read(fd, &var.buffer, 0) < 0)
		return (line[fd] = ft_sfree(line[fd]), NULL);
	if (!line[fd])
		line[fd] = ft_gnl_calloc(1, sizeof(char));
	var.buffer = ft_gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	var.pos = 0;
	while (ft_find(line[fd]) == 0)
	{
		ft_gnl_bzero(var.buffer, BUFFER_SIZE + 1);
		var.rd = read(fd, var.buffer, BUFFER_SIZE);
		if (var.rd <= 0)
			break ;
		line[fd] = ft_gnl_strjoin(line[fd], var.buffer);
	}
	var.buffer = ft_sfree(var.buffer);
	if (var.rd == -1 || (var.rd <= 0 && *line[fd] == 0))
		return (line[fd] = ft_sfree(line[fd]), NULL);
	var.next_line = ft_small_split(line[fd], &var.pos);
	var.buffer = line[fd];
	line[fd] = ft_gnl_strjoin(NULL, line[fd] + var.pos);
	return (var.buffer = ft_sfree(var.buffer), var.next_line);
}
