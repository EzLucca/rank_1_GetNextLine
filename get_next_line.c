/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:07:46 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/15 17:51:05 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_from_file(int fd, char *raw_data, int *bytes_read)
{
	char	*buffer;
	char	*temp;

	if (!raw_data)
	{
		raw_data = malloc(1 * sizeof(char));
		raw_data[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	*bytes_read = 1;
	while(!ft_strchr(raw_data, '\n'))
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
		{
			free(buffer);
			free(raw_data);
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		temp = raw_data;
		raw_data = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (raw_data);
}

static char *filtered(char *raw_data)
{
	int	i;
	char *line_filtered;

	i = 0;
	if (!raw_data || !raw_data[i])
		return (NULL);
	while(raw_data[i] && raw_data[i] != '\n')
		i++;
	line_filtered = malloc(i + 2 * sizeof(char));
	if (!line_filtered)
		return (NULL);
	i = 0;
	while (raw_data[i] && raw_data[i] != '\n')
	{
		line_filtered[i] = raw_data[i];
		i++;
	}
	if (raw_data[i] == '\n')
	{
		line_filtered[i] = raw_data[i];
		i++;
	}
	line_filtered[i] = '\0';
	return (line_filtered);
}

static char *rest_of(char *raw_data)
{
	int i;
	int	j;
	char *rest_line;

	i = 0;
	while (raw_data[i] && raw_data[i] != '\n')
		i++;
	if (!raw_data[i])
	{
		free(raw_data);
		return (NULL);
	}
	rest_line = malloc((ft_strlen(raw_data) - i + 1) * sizeof(char));
	if (!rest_line)
		return (NULL);
	i++;
	j = 0;
	while (raw_data[i])
		rest_line[j++] = raw_data[i++];
	free(raw_data);
	return (rest_line);
}

char *get_next_line(int fd)
{
	char *next_line;
	static char *raw_data;
	int	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	raw_data = read_from_file(fd, raw_data, &bytes_read);
	if (!raw_data )
		return (NULL);
	next_line = filtered(raw_data);
	raw_data = rest_of(raw_data);
	if (!next_line && bytes_read == 0)
	{
		free(raw_data);
		return (NULL);
	}
	return (next_line);
}

