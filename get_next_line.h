/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:01:03 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/13 18:07:08 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# define BUFFER_SIZE = 1024

// ------------------------ Librarys ------------------------ //

# include <unistd.h>
# include <stdlib.h>

// ------------------------ Prototypes ------------------------ //

void	*ft_calloc(size_t nmemb, size_t size);

void	ft_bzero(void *s, size_t n);

char *get_next_line(int fd);


#endif // !GET_NEXT_LINE
