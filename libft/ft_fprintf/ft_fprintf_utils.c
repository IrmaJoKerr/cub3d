/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:34:00 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/22 18:52:59 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_left_align(t_flags flags, char *buffer
						, const char *data, int padding)
{
	int	data_len;
	int	start;

	data_len = ft_strlen(data);
	start = 0;
	if (flags.width > flags.precision)
		start = flags.width - flags.precision;
	if (flags.precision > 0)
	{
		if (start == 0 && flags.precision > data_len)
			start = flags.precision - data_len;
		else if (flags.width > flags.precision)
			start = flags.precision - data_len;
		if (start < 0)
			start = 0;
		ft_fill_buffer(buffer, ' ', start, padding + data_len);
		ft_fill_buffer(buffer, '0', 0, start);
		ft_memcpy(buffer + start, data, data_len);
	}
	else
	{
		ft_memcpy(buffer, data, data_len);
		ft_fill_buffer(buffer, ' ', data_len, data_len + padding);
	}
}

void	ft_right_align(t_flags flags, char *buffer
						, const char *data, int padding)
{
	int	data_len;
	int	start;

	data_len = ft_strlen(data);
	start = 0;
	if (flags.width > flags.precision)
		start = flags.width - flags.precision;
	if (flags.zero_padding && !flags.has_precision)
		ft_fill_buffer(buffer, '0', 0, padding);
	else if (flags.precision > 0)
	{
		if (flags.precision > flags.width && flags.precision > data_len)
			padding = flags.precision - data_len;
		ft_fill_buffer(buffer, ' ', 0, padding);
		ft_fill_buffer(buffer, '0', start, padding);
	}
	else
		ft_fill_buffer(buffer, ' ', 0, padding);
	ft_memcpy(buffer + padding, data, data_len);
}

void	ft_insert_into_buffer(char *buffer, const char *data, t_flags flags)
{
	int	data_len;
	int	padding;

	data_len = ft_strlen(data);
	padding = flags.width - data_len;
	if (padding <= 0 && (flags.precision > 0 && flags.precision > data_len))
		padding = flags.precision - data_len;
	else if (padding < 0)
		padding = 0;
	buffer[data_len + padding] = '\0';
	if (flags.left_align)
		ft_left_align(flags, buffer, data, padding);
	else
		ft_right_align(flags, buffer, data, padding);
}

char	*ft_itoa_base(unsigned long value, const char *base)
{
	unsigned int	base_len;
	unsigned long	temp;
	int				len;
	char			*str;

	base_len = ft_strlen(base);
	temp = value;
	len = 1;
	temp = value / base_len;
	while (temp)
	{
		temp /= base_len;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[value % base_len];
		value /= base_len;
	}
	return (str);
}
