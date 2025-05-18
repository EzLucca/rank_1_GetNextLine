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

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# define BUFFER_SIZE 42 
# define MAX_FD 1024

// ------------------------ Libraries ------------------------ //

# include <unistd.h>
# include <stdlib.h>

// ------------------------ Prototypes ------------------------ //

void	*ft_calloc(size_t nmemb, size_t size);

void	ft_bzero(void *s, size_t n);

char *get_next_line(int fd);

size_t	ft_strlen(const char *s);

char	*ft_strjoin(char const *s1, char const *s2);

void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s);

char	*ft_strjoin_and_free(char *s1, char *s2);

#endif // !GET_NEXT_LINE

