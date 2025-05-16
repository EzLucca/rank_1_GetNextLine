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

static char *read_from_file(int fd, char *buffer, int *bytes_read)
{
	char	*tmp_buffer;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	tmp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	*bytes_read = 1;
	while(!ft_strchr(buffer, '\n'))
	{
		*bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (*bytes_read < 0)
		{
			free(tmp_buffer);
			free(buffer);
			return (NULL);
		}
		if (*bytes_read == 0)
			break;
		tmp_buffer[*bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tmp_buffer);
	}
	free(tmp_buffer);
	return (buffer);
}

static char	*rest_of_line(const char *s, int c)
{
	int	i;

	c = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i+1]);
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i+1]);
	return (NULL);
}

static char *filtered(char *buffer)
{
	int	i;
	char *line_to_return;

	if (!buffer || !buffer[i])
		return (NULL);
	i = ft_strlen(buffer) - ft_strlen(rest_of_line(buffer, '\n'));
	line_to_return = ft_calloc(i + 2, sizeof(char));
	if (!line_to_return)
		return (NULL);
	ft_memcpy(line_to_return, buffer, i);
	return (line_to_return);
}


char	*get_next_line(int fd)
{
	char *next_line;
	static char *buffer;
	int	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_from_file(fd, buffer, &bytes_read);
	if (!buffer )
		return (NULL);
	next_line = filtered(buffer);
	buffer = rest_of_line(buffer, '\n');
	if (!next_line && bytes_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (next_line);
}
