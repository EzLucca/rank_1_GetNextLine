/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:00:41 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/15 17:28:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	p;

	p = 0;
	while (*s++)
		++p;
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (unsigned char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*tmp_dst;
	const unsigned char		*tmp_src;

	tmp_dst = (unsigned char *) dest;
	tmp_src = (const unsigned char *) src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*array;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	array = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	ft_memcpy(array, s1, s1_len);
	ft_memcpy(array + s1_len, s2, s2_len);
	array[s1_len + s2_len] = '\0';
	return (array);
}

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (newstr)
	{
		while (s[i])
		{
			newstr[i] = s[i];
			i++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
