/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:42:02 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/01/03 13:06:12 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*remain;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remain = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!remain)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		remain[j++] = buffer[i++];
	free(buffer);
	return (remain);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;
	char	*tmp;

	if (!res)
		res = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(res, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(res);
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		tmp = ft_strjoin(res, buffer);
		free(res);
		res = tmp;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffers[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX)
		return (NULL);
	if (!buffers[fd])
		buffers[fd] = ft_calloc(1, sizeof(char));
	buffers[fd] = read_file(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = ft_line(buffers[fd]);
	if (!line)
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	buffers[fd] = ft_remainder(buffers[fd]);
	return (line);
}
