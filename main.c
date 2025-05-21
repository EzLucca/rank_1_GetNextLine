/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:26:12 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/19 13:53:34 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("lord.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		count++;
		printf("[%d] -> %s", count, next_line);
		free (next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
}
