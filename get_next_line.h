/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:01:03 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/19 13:50:10 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1112 
# endif

// ------------------------ Libraries ------------------------ //

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// ------------------------ Prototypes ------------------------ //

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);

void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_substr(char *s, unsigned int start, size_t len);

char	*ft_strdup(char *s);
#endif
