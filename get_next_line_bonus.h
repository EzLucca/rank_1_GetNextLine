/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:17:56 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/18 18:18:31 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19 
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

// ------------------------ Libraries ------------------------ //

# include <unistd.h>
# include <stdlib.h>

// ------------------------ Prototypes ------------------------ //

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);

void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_substr(char *s, unsigned int start, size_t len);

#endif 
