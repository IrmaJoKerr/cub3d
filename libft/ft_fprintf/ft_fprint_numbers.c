/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:23:10 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/22 18:59:29 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_printint_utils(t_flags flags, char *buffer, char *temp, char sign)
{
	int	len;

	if (temp[0] == '0' && flags.width != 0
		&& flags.has_precision && flags.precision == 0)
		temp[0] = '\0';
	ft_insert_into_buffer(buffer, temp, flags);
	len = ft_strlen(buffer);
	if (sign && (flags.width > flags.precision)
		&& flags.zero_padding && flags.has_precision)
	{
		write(flags.fd, " ", 1);
		if (ft_strlen(temp) > (size_t)flags.precision)
			flags.precision = len - ft_strlen(temp) + 1;
		ft_fill_buffer(buffer, '-', flags.precision - 2, flags.precision - 1);
	}
	else if (sign)
		write(flags.fd, &sign, 1);
	if (flags.space_sign && !sign)
		write(flags.fd, " ", 1);
	else if (flags.plus_sign && !sign)
		write(flags.fd, "+", 1);
	if (flags.plus_sign || flags.space_sign || sign)
		len++;
	write(flags.fd, buffer, strlen(buffer));
	return (len);
}

char	*ft_handle_sign(int num, t_flags *flags, char *sign)
{
	char	*temp;

	if (num < 0 && (flags->zero_padding || flags->precision > 0
			|| (!flags->has_precision && !flags->width)))
	{
		*sign = '-';
		if (num == -2147483648)
			temp = ft_strdup("2147483648");
		else
			temp = ft_itoa(-num);
		flags->width--;
	}
	else
		temp = ft_itoa(num);
	return (temp);
}

int	ft_printint(int num, t_flags flags)
{
	char	*temp;
	int		len;
	char	sign;
	char	*buffer;

	sign = 0;
	if (num == 0 && flags.has_precision
		&& flags.precision == 0 && flags.width == 0)
		return (0);
	if (flags.precision > flags.width)
		flags.width = flags.precision;
	temp = ft_handle_sign(num, &flags, &sign);
	buffer = ft_calloc_buffer(temp, flags);
	len = ft_printint_utils(flags, buffer, temp, sign);
	free(temp);
	free(buffer);
	return (len);
}

int	ft_printpercent(t_flags flags)
{
	char	temp[2];
	char	*buffer;
	int		len;

	temp[0] = '%';
	temp[1] = '\0';
	buffer = ft_calloc_buffer(temp, flags);
	ft_insert_into_buffer(buffer, temp, flags);
	len = ft_strlen(buffer);
	write(flags.fd, buffer, len);
	free(buffer);
	return (len);
}

int	ft_printunsigned(unsigned int num, t_flags flags)
{
	char	*temp;
	int		len;
	char	*buffer;

	if (num == 0 && flags.has_precision
		&& flags.precision == 0 && flags.width == 0)
		return (0);
	temp = ft_itoa_base(num, "0123456789");
	if (!temp)
		return (-1);
	if (temp[0] == '0' && flags.width != 0
		&& flags.has_precision && flags.precision == 0)
		temp[0] = '\0';
	buffer = ft_calloc_buffer(temp, flags);
	ft_insert_into_buffer(buffer, temp, flags);
	len = ft_strlen(buffer);
	write(flags.fd, buffer, len);
	free(temp);
	free(buffer);
	return (len);
}
