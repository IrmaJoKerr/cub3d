/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:52:47 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/11/15 16:38:45 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hit_words(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_hit_words(s1[start], set))
		start++;
	while (end > start && ft_hit_words(s1[end - 1], set))
		end--;
	tmp = (char *) malloc((end - start + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, s1 + start, end - start + 1);
	return (tmp);
}
