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

static char	*read_from_file(int fd, char *buffer)
{
	char	*tmp_buf;
	char	*new_joined_buffer;
	ssize_t	bytes_read;

	tmp_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buf)
		return (free(tmp_buf), NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(tmp_buf), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		tmp_buf[bytes_read] = '\0';
		new_joined_buffer = ft_strjoin(buffer, tmp_buf);
		free (buffer);
		buffer = new_joined_buffer;
		if (!buffer)
			return (free(tmp_buf), NULL);
	}
	free (tmp_buf);
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
		return (free(buffer), NULL);
	rest_len = ft_strlen(newline_ptr + 1);
	rest_of_line = ft_substr(newline_ptr + 1, 0, rest_len);
	if (!rest_of_line)
		return (free(buffer), NULL);
	free(buffer);
	return (rest_of_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	if (line == NULL)
		return (NULL);
	return (line);
}
