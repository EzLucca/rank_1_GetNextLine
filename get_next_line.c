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

char *read_from_file(int fd, char *buffer, int *bytes_read)
{
	char	*tmp_buffer;
	char	*temp;

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
		tmp_buffer[*bytes_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin(temp, tmp_buffer);
		free(temp);
	}
	free(tmp_buffer);
	return (buffer);
}

static char *filtered(char *buffer)
{
	int	i;
	char *line_filtered;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while(buffer[i] && buffer[i] != '\n')
		i++;
	line_filtered = ft_calloc(i + 2, sizeof(char));
	if (!line_filtered)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line_filtered[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line_filtered[i] = buffer[i];
		i++;
	}
	return (line_filtered);
}

static char *rest_of(char *buffer)
{
	int i;
	int	j;
	char *rest_line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	rest_line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!rest_line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		rest_line[j++] = buffer[i++];
	free(buffer);
	return (rest_line);
}

char *get_next_line(int fd)
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
	buffer = rest_of(buffer);
	if (!next_line && bytes_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (next_line);
}
