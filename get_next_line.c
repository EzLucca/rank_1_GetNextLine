/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:07:46 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/15 21:42:23 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char *read_from_file(int fd, char *buffer)
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
		if (bytes <= 0)
			break;
		temp[bytes] = '\0';
		line = ft_strjoin_and_free(line, temp);
		if (!line)
			return (NULL);
	}
	return (line);
}

static void	rest_of_line(char *buffer, char *line)
{
	int		i;
	char	*newline;

	i = 0;
	newline = ft_strchr(line, '\n');
	if (!newline)
	{
		buffer[0] = '\0';
		return ;
	}
	newline++;
	while (*newline)
		buffer[i++] = *newline++;
	buffer[i] = '\0';
}

static char *extract_line(char *line)
{
	int	i;
	char *line_to_return;

	i = 0;
	if (!line || !line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	line_to_return = ft_calloc(i + 1, sizeof(char));
	if (!line_to_return)
		return (NULL);
	ft_memcpy(line_to_return, line, i);
	return (line_to_return);
}

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*result;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0] == '\0')
		ft_bzero(buffer, BUFFER_SIZE + 1);
	line = read_from_file(fd, buffer);
	if (!line)
		return (NULL);
	result = extract_line(line);
	if (!result)
		return (free(line), NULL);
	rest_of_line(buffer, line);
	free(line);
	return (result);
}
