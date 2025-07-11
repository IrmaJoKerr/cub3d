/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils_sub.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:37:59 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/22 18:52:14 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

char	*ft_calloc_buffer(char *data, t_flags flags)
{
	char	*buffer;
	int		data_len;
	int		buffer_size;

	data_len = ft_strlen(data);
	buffer_size = data_len;
	if (flags.has_precision && flags.precision > data_len)
		buffer_size = flags.precision;
	if (flags.width > buffer_size)
		buffer_size = flags.width;
	buffer = (char *)ft_calloc(buffer_size + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	return (buffer);
}

void	ft_adjust_flags(t_flags *flags)
{
	if (flags->left_align)
		flags->zero_padding = false;
}

void	ft_fill_buffer(char *buffer, char fill_char, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
		buffer[i++] = fill_char;
}
