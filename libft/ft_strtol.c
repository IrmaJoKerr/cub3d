/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:51:22 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/07/06 13:29:53 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_spaces_and_sign(const char *str, int *sign)
{
	*sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static int	char_to_digit(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (10 + (c - 'a'));
	else if (c >= 'A' && c <= 'Z')
		return (10 + (c - 'A'));
	else
		return (-1);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	if (base < 2 || base > 36)
		return (0);
	str = skip_spaces_and_sign(str, &sign);
	while (*str)
	{
		digit = char_to_digit(*str++);
		if (digit < 0 || digit >= base)
			break ;
		if (result > (LONG_MAX - digit) / base)
		{
			if (sign == 1)
				return (LONG_MAX);
			else if (sign == -1)
				return (LONG_MIN);
		}
		result = result * base + digit;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
