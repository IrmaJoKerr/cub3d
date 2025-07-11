/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:23:42 by wjun-kea          #+#    #+#             */
/*   Updated: 2024/11/17 14:02:29 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_token(const char *str, char c)
{
	int	i;
	int	token;

	i = 0;
	token = 0;
	while (*str)
	{
		if (*str != c && token == 0)
		{
			i++;
			token = 1;
		}
		else if (*str == c)
			token = 0;
		str++;
	}
	return (i);
}

static char	*wordgen(const char *str, int start, int end)
{
	char	*words;
	int		i;

	i = 0;
	words = (char *) malloc((end - start + 1) * sizeof(char));
	if (!words)
		return (NULL);
	while (start < end)
		words[i++] = str[start++];
	words[i] = '\0';
	return (words);
}

static void	free_tokens(char **tokens, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static int	fill_tokens(char **tokens, const char *s, char c)
{
	int		index;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	index = -1;
	while (x <= ft_strlen(s))
	{
		if (s[x] != c && index < 0)
			index = x;
		else if ((s[x] == c || x == ft_strlen(s)) && index >= 0)
		{
			tokens[y] = wordgen(s, index, x);
			if (!tokens[y])
				return (y);
			y++;
			index = -1;
		}
		x++;
	}
	tokens[y] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tokens;
	size_t	num;

	if (!s)
		return (NULL);
	tokens = (char **) malloc((count_token(s, c) + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	num = fill_tokens(tokens, s, c);
	if (num)
	{
		free_tokens(tokens, num);
		return (NULL);
	}
	return (tokens);
}
