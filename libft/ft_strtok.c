/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:51:48 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/06/27 22:29:18 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static void	handle_quotes(const char **ptr,
			bool *in_quotes)
{
	while (**ptr)
	{
		if (is_quote(**ptr))
			*in_quotes = !(*in_quotes);
		else
			break ;
		(*ptr)++;
	}
}

static void	move_to_next_token(const char **saved_str,
					const char *delim, bool *in_quotes)
{
	while (**saved_str)
	{
		if (is_quote(**saved_str))
			*in_quotes = !(*in_quotes);
		else if (!(*in_quotes) && ft_strchr(delim, **saved_str))
			break ;
		(*saved_str)++;
	}
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str;
	char		*token;
	bool		in_quotes;
	char		*end;

	in_quotes = false;
	if (str != NULL)
		saved_str = str;
	if (saved_str == NULL)
		return (NULL);
	handle_quotes((const char **)&saved_str, &in_quotes);
	if (*saved_str == '\0')
		return (NULL);
	token = saved_str;
	move_to_next_token((const char **)&saved_str, delim, &in_quotes);
	if (*saved_str != '\0')
		*(saved_str++) = '\0';
	if (is_quote(*token))
		token++;
	end = token + ft_strlen(token) - 1;
	if (is_quote(*end))
		*end = '\0';
	return (token);
}
