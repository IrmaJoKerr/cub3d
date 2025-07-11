/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:50:00 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/22 18:52:01 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_handle_format(const char format_char, va_list args, t_flags flags)
{
	int		count;

	if (format_char == 'c')
		count = ft_printchar(va_arg(args, int), flags);
	else if (format_char == 's')
		count = ft_printstr(va_arg(args, char *), flags);
	else if (format_char == 'd' || format_char == 'i')
		count = ft_printint(va_arg(args, int), flags);
	else if (format_char == 'u')
		count = ft_printunsigned(va_arg(args, unsigned int), flags);
	else if (format_char == 'x')
		count = ft_printhex(va_arg(args, unsigned int), flags);
	else if (format_char == 'X')
		count = ft_printupperhex(va_arg(args, unsigned int), flags);
	else if (format_char == 'p')
		count = ft_printvoid(va_arg(args, void *), flags);
	else if (format_char == '%')
		count = ft_printpercent(flags);
	return (count);
}

int	ft_handle_width(const char *format, int *i, t_flags *flags)
{
	while (ft_isdigit(format[*i]))
	{
		flags->width = flags->width * 10 + format[*i] - '0';
		(*i)++;
	}
	if (format[*i] == '.')
	{
		flags->has_precision = true;
		(*i)++;
		while (ft_isdigit(format[*i]))
		{
			flags->precision = flags->precision * 10 + format[*i] - '0';
			(*i)++;
		}
	}
	return (0);
}

int	ft_handle_flags(const char *format, int *i, t_flags *flags)
{
	while (format[*i] == '-' || format[*i] == '0' || format[*i] == '+'
		|| format[*i] == ' ' || format[*i] == '#')
	{
		if (format[*i] == '-')
			flags->left_align = true;
		else if (format[*i] == '0')
			flags->zero_padding = true;
		else if (format[*i] == '+')
			flags->plus_sign = true;
		else if (format[*i] == ' ')
			flags->space_sign = true;
		else if (format[*i] == '#')
			flags->alternate_form = true;
		(*i)++;
	}
	ft_adjust_flags(flags);
	return (0);
}

void	init_flags(t_flags *flags, int fd)
{
	flags->left_align = false;
	flags->zero_padding = false;
	flags->plus_sign = false;
	flags->space_sign = false;
	flags->alternate_form = false;
	flags->has_precision = false;
	flags->width = 0;
	flags->precision = 0;
	flags->fd = fd;
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;
	t_flags	flags;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		init_flags(&flags, fd);
		if (format[i] == '%')
		{
			i++;
			ft_handle_flags(format, &i, &flags);
			ft_handle_width(format, &i, &flags);
			count += ft_handle_format(format[i++], args, flags);
		}
		else
			count += ft_printchar(format[i++], flags);
	}
	va_end(args);
	return (count);
}
