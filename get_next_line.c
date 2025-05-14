/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:00:04 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/14 17:32:18 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read and store the raw_data characteres
char *read_from_file(int fd, char *raw_data, int *bytes_read)
{
	char	*buffer;
	char	*temp;

	// check if raw_data is not empty
	if (!raw_data)
		raw_data = malloc(1 * sizeof(char));
	// reserving the memory space with the BUFFER_SIZE
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	// initialize bytes_read 
	*bytes_read = 1;
	// check for specifier \n and read the file and storing the content in raw_data
	// and the number of bytes in bytes_read
	// if no bytes were readed then free the raw_data and return NULL.
	while(!ft_strchr(raw_data, '\n') /*&& *bytes_read != 0 is necessary?*/)
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

// Function to filterd the raw_data result and return the lines.
// Here I need to check for the new line specifier and store
// the characters in the line to be returned.
static char *filtered(char *raw_data)
{
	int	i;
	int	len;
	char *line_filtered;

	len = 0;
	// Check if raw_data is not empty.
	if (!raw_data[len])
		return (NULL);
	// While the raw_data exist and is different than the \n 
	// (This means it found a line) it will count the number of elements.
	while(raw_data[len] && raw_data[len] != '\n')
		len++;
	// Create the memory space and the 2 means \n and \0.
	line_filtered = malloc(len + 2 * sizeof(char));
	if (!line_filtered)
		return (NULL);
	// Puts the char from raw_data in line_filtered (one line)
	i = 0;
	while (i < len)
	{
		line_filtered[i] = raw_data[i];
		i++;
	}
	// Null terminate the string.
	line_filtered[i] = '\0';
	return (line_filtered);
}

// Function to store the rest_of of the raw_data lines 
// Because the number of elements might be different I need to store 
// the rest_of after the \n in a variable 
static char *rest_of(char *raw_data)
{
	int i;
	int	j;
	char *rest_line;

	i = 0;
	// 
	while (raw_data[i] && raw_data[i] != '\n')
		i++;
	if (!raw_data[i])
	{
		free(raw_data);
		return (NULL);
	}
	rest_line = malloc(ft_strlen(raw_data) - i + 1 * sizeof(char));
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
	static char *raw_data[1024];
	int	bytes_read;

	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
	raw_data[fd] = read_from_file(fd, raw_data[fd], &bytes_read);
	if (!raw_data[fd] )
		return (NULL);
	next_line = filtered(raw_data[fd]);
	raw_data[fd] = rest_of(raw_data[fd]);
	if (!next_line && bytes_read == 0)
	{
		free(raw_data[fd]);
		return (NULL);
	}
	return (next_line);
}
