/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:12:30 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/22 19:00:04 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_printchar_utils(t_flags flags, char *buffer, int len)
{
	if (flags.width > 0 && !flags.left_align)
	{
		ft_fill_buffer(buffer, ' ', 0, flags.width - 1);
		write(flags.fd, buffer, flags.width);
		len = flags.width;
	}
	else if (flags.width > 0 && flags.left_align)
	{
		write(flags.fd, "\0", 1);
		while (len++ < flags.width)
			write(flags.fd, " ", 1);
		len = flags.width;
	}
	else
		write(flags.fd, "\0", len);
	return (len);
}

int	ft_printchar(int c, t_flags flags)
{
	char	temp[2];
	int		len;
	char	*buffer;

	c = (c + 256) % 256;
	temp[0] = (char)c;
	temp[1] = '\0';
	len = 1;
	if (flags.width > 0 || flags.has_precision || flags.left_align || c == 0)
		buffer = ft_calloc_buffer(temp, flags);
	else
		buffer = NULL;
	if (c == 0)
		len = ft_printchar_utils(flags, buffer, len);
	else if (flags.width > 0 || flags.has_precision || flags.left_align)
	{
		ft_insert_into_buffer(buffer, temp, flags);
		len = ft_strlen(buffer);
		write(flags.fd, buffer, len);
	}
	else
		write(flags.fd, temp, len);
	free(buffer);
	return (len);
}

int	ft_printstr_utils(t_flags flags, char *buffer, int len, const char *temp)
{
	if (flags.has_precision && flags.precision != 0 && buffer)
	{
		if (ft_strncmp(temp, "(null)", 6) == 0 && flags.precision < 6)
			return (0);
		else
			flags.precision = 0;
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
	else
	{
		write(flags.fd, " ", flags.width);
		len = flags.width;
	}
	return (len);
}

int	ft_printstr(const char *str, t_flags flags)
{
	int		len;
	char	*temp;
	char	*buffer;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.precision > 0 && flags.precision < len
		&& ft_strncmp(str, "(null)", 6) != 0)
		len = flags.precision;
	temp = malloc(len + 1);
	if (!temp)
		return (-1);
	ft_strncpy(temp, str, len);
	temp[len] = '\0';
	buffer = ft_calloc_buffer(temp, flags);
	len = ft_printstr_utils(flags, buffer, len, temp);
	free(temp);
	free(buffer);
	return (len);
}
