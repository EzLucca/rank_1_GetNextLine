/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:26:12 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/18 15:32:05 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	int    fd1;
	int    fd2;
	char  *next_line1;
	char  *next_line2;
	int  count;

	count = 0;
	fd1 = open("lord.txt", O_RDONLY);
	fd2 = open("rings.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (1);
	while(1)
	{
		next_line1 = get_next_line(fd1);
		next_line2 = get_next_line(fd2);
		if (!next_line1 || !next_line2)
			break ;
		count++;
		printf("fd1 - %d -> %s", count, next_line1); //count is to show you the line numbers
		printf("fd2 - %d -> %s", count, next_line2); //count is to show you the line numbers
		free (next_line1);
		free (next_line2);
		// next_line = NULL;
	}

	close(fd1);
	close(fd2);
	return (0);
}
