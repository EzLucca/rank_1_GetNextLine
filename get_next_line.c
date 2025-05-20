/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:07:46 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/19 17:57:50 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *buffer)
{
	char	*tmp_buf;
	ssize_t	bytes_read;

	tmp_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(tmp_buf);
			free(buffer);
			return (NULL);
		}
		tmp_buf[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tmp_buf);
		if (!buffer)
			return (free(tmp_buf), NULL);
	}
	free(tmp_buf);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_substr(buffer, 0, i + 1);
	else
		line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*rest_of_line;
	char	*newline_ptr;
	size_t	rest_len;

	newline_ptr = ft_strchr(buffer, '\n');
	if (!newline_ptr)
	{
		free(buffer);
		return (NULL);
	}
	rest_len = ft_strlen(newline_ptr + 1);
	rest_of_line = ft_substr(newline_ptr + 1, 0, rest_len);
	free(buffer);
	return (rest_of_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(1);
	ft_memcpy(buffer, "", 1);
	buffer[0] = '\0';
	buffer = read_to_stash(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
