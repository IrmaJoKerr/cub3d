/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:46:12 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/12/05 08:59:31 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_1;
	size_t	len_2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	dst = ft_calloc(len_1 + len_2 + 1, sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len_1)
	{
		dst[i] = s1[i];
		i++;
	}
	while (*s2)
		dst[i++] = *(s2++);
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	unsigned char	*tmp;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = nmemb * size;
	if (nmemb > 4294967295 / size)
		return (NULL);
	tmp = malloc(total_size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < total_size)
		tmp[i++] = 0;
	return (tmp);
}

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (*c != '\0')
	{
		i++;
		c++;
	}
	return (i);
}
