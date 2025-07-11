/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:36:55 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/11/08 12:47:33 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	dst = (char *) malloc((len_1 + len_2 + 1) * sizeof(char));
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
