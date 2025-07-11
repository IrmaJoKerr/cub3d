/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:30:27 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/11/09 17:13:16 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		l;

	l = 0;
	s = src;
	while (*s++)
		l++;
	if (size > 0)
	{
		while (*src && size > 1)
		{
			*(dst++) = *(src++);
			size--;
		}
		*dst = '\0';
	}
	return (l);
}
