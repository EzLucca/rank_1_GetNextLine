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
	// check if raw_data is not empty
	if (!raw_data)
	{
		raw_data = malloc(1 * sizeof(char));
		return (raw_data);
	}
	// reserving the memory space with the BUFFER_SIZE
	raw_data = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!raw_data )
		return (NULL);
	// initialize bytes_read 
	*bytes_read = 1;
	// check for specifier \n and read the file and storing the content in raw_data
	// and the number of bytes in bytes_read
	// if no bytes were readed then free the raw_data and return NULL.
	while(!ft_strchr(raw_data, '\n') /*&& *bytes_read != 0 is necessary?*/)
	{
		*bytes_read = read(fd, raw_data, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(raw_data);
			return (NULL);
		}
	}
	// NULL terminate the raw_data.
	raw_data[BUFFER_SIZE] = '\0';
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
	if (!raw_data)
		return (NULL);
	// While the raw_data exist and is different than the \n 
	// (This means it found a line) it will count the number of elements.
	while(raw_data[i] && raw_data[i] != '\n')
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

// Function to store the remainder of the raw_data lines 
// Because the number of elements might be different I need to store 
// the remainder after the \n in a variable 
static char *remainder(char *raw_data)
{
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
	raw_data[fd] = remainder(raw_data[fd]);
	if (!next_line && bytes_read == 0)
	{
		free(raw_data[fd]);
		return (NULL);
	}
	return (next_line);
}
