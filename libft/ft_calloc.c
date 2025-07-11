/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:44:22 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/11/15 09:47:43 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
