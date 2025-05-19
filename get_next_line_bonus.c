/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:29:04 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/18 18:34:05 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*read_from_file(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	char	*line;
	int		bytes;

	line = NULL;
	if (buffer[0] != '\0')
		line = ft_strjoin_and_free(NULL, buffer);
	else
		line = ft_strjoin_and_free(NULL, "");
	if (!line)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(line, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(line), NULL);
		temp[bytes] = '\0';
		line = ft_strjoin_and_free(line, temp);
		if (!line)
			return (NULL);
	}
	return (line);
}

static char	*extract_line(char *buffer, char *line)
{
	int		len;
	char	*newline;
	char	*line_to_return;

	if (!line || !line[0])
		return (NULL);
	newline = ft_strchr(line, '\n');
	if (!newline)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	len = newline - line + 1;
	newline++;
	ft_memcpy(buffer, newline, ft_strlen(newline));
	buffer[ft_strlen(newline)] = '\0';
	line_to_return = ft_calloc(len + 1, sizeof(char));
	if (!line_to_return)
		return (NULL);
	ft_memcpy(line_to_return, line, len);
	return (line_to_return);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*line;
	char		*result;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_from_file(fd, buffer[fd]);
	if (!line)
		return (NULL);
	result = extract_line(buffer[fd], line);
	if (!result)
		return (free(line), NULL);
	free(line);
	return (result);
}
