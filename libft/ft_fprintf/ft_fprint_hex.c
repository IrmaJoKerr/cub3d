/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:35:47 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/22 19:00:27 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_printhex_utils(t_flags flags, char *buffer, char *temp, int len)
{
	if (flags.has_precision && flags.precision != 0 && buffer)
	{
		ft_insert_into_buffer(buffer, temp, flags);
		len = ft_strlen(buffer);
		write(flags.fd, buffer, len);
	}
	else if (!flags.has_precision && buffer)
	{
		ft_insert_into_buffer(buffer, temp, flags);
		len = ft_strlen(buffer);
		write(flags.fd, buffer, len);
	}
	else if (flags.has_precision && temp[0] != '0')
	{
		ft_insert_into_buffer(buffer, temp, flags);
		len = ft_strlen(buffer);
		write(flags.fd, buffer, len);
	}
	else
	{
		while (len++ != flags.width)
			write(flags.fd, " ", 1);
		len--;
	}
	return (len);
}

char	*handle_alternate_form(char *temp, unsigned int num
								, t_flags flags, char *data)
{
	char	*result;

	if (flags.alternate_form && num != 0)
	{
		result = temp;
		temp = ft_strjoin(data, temp);
		free(result);
	}
	return (temp);
}

int	ft_printupperhex(unsigned int num, t_flags flags)
{
	char	*temp;
	int		len;
	char	*buffer;

	len = 0;
	if (num == (unsigned int)-1)
	{
		if (flags.precision < 8 && flags.has_precision)
			flags.precision = 8;
		temp = ft_strdup("FFFFFFFF");
	}
	else
		temp = ft_itoa_base(num, "0123456789ABCDEF");
	if (!temp)
		return (-1);
	temp = handle_alternate_form(temp, num, flags, "0X");
	buffer = ft_calloc_buffer(temp, flags);
	len = ft_printhex_utils(flags, buffer, temp, len);
	free(temp);
	free(buffer);
	return (len);
}

int	ft_printhex(unsigned int num, t_flags flags)
{
	char	*temp;
	int		len;
	char	*buffer;

	len = 0;
	if (num == (unsigned int)-1)
	{
		if (flags.precision < 8 && flags.has_precision)
			flags.precision = 8;
		temp = ft_strdup("ffffffff");
	}
	else
		temp = ft_itoa_base(num, "0123456789abcdef");
	if (!temp)
		return (-1);
	temp = handle_alternate_form(temp, num, flags, "0x");
	buffer = ft_calloc_buffer(temp, flags);
	len = ft_printhex_utils(flags, buffer, temp, len);
	free(temp);
	free(buffer);
	return (len);
}

int	ft_printvoid(void *ptr, t_flags flags)
{
	unsigned long	addr;
	char			*temp;
	char			*full_addr;
	int				len;
	char			*buffer;

	if (!ptr)
		return (ft_printstr("(nil)", flags));
	addr = (unsigned long)ptr;
	temp = ft_itoa_base(addr, "0123456789abcdef");
	if (!temp)
		return (-1);
	full_addr = ft_strjoin("0x", temp);
	free(temp);
	if (!full_addr)
		return (-1);
	buffer = ft_calloc_buffer(full_addr, flags);
	ft_insert_into_buffer(buffer, full_addr, flags);
	len = ft_strlen(buffer);
	write(flags.fd, buffer, len);
	free(full_addr);
	free(buffer);
	return (len);
}
