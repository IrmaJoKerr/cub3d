/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:04:21 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/02/18 19:45:31 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	char	*dest;

	if (!s)
		return (NULL);
	tmp = (char *) malloc(ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	dest = tmp;
	while (*s)
	{
		*tmp = *s;
		tmp++;
		s++;
	}
	*tmp = '\0';
	return (dest);
}
