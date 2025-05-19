/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:00:41 by edlucca           #+#    #+#             */
/*   Updated: 2025/05/15 21:26:36 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	p;

	if (!s)
		return (0);
	p = 0;
	while (s[p])
		p++;
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	char	*temp_ptr;

	temp_ptr = (char *) s;
	while (n > 0)
	{
		*(temp_ptr++) = 0;
		n--;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*tmp_dst;
	const unsigned char		*tmp_src;

	if (!dest || !src)
		return (NULL);
	tmp_dst = (unsigned char *) dest;
	tmp_src = (const unsigned char *) src;
	while (n--)
		*(tmp_dst++) = *(tmp_src++);
	return (dest);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*strjoined;

	if (!s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	len2 = ft_strlen(s2);
	strjoined = malloc((len1 + len2 + 1) * sizeof(char));
	if (!strjoined)
		return (free(s1), NULL);
	if (s1)
		ft_memcpy(strjoined, s1, len1);
	ft_memcpy(strjoined + len1, s2, len2);
	strjoined[len1 + len2] = '\0';
	free((void *) s1);
	return (strjoined);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;
	size_t	nb_bytes;

	nb_bytes = nmemb * size;
	if (size && (nb_bytes / size) != nmemb)
		return (NULL);
	tmp = malloc(nb_bytes);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nb_bytes);
	return (tmp);
}
