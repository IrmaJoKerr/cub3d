/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:57:18 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 15:34:18 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <fcntl.h>

int	validate_line(char *line, int line_num, t_game *game);
int	validate_chars(char *line, t_game *game, int len);
int	chk_first_and_last_line(char *line);
int	chk_inside_lines(char *line, t_game *game);
int	count_lines(const char *filename);

/*
Validates the characters in the map.
*/
int	validate_chars(char *line, t_game *game, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strchr(VALID_CHARS, line[i]))
			return (0);
		if (line[i] == 'P')
			game->map.herocount++;
		i++;
	}
	return (1);
}

/*
Validates map lines using flag-based approach.
First and last lines are validated as border lines (all '1's).
Interior lines are validated as having '1' at start/end with
valid characters inside.
*/
int	validate_line(char *line, int line_num, t_game *game)
{
	int	len;

	len = ft_strlen(line);
	if (len > game->map.max_cols)
		game->map.max_cols = len;
	if (line_num == 0)
	{
		if (!chk_first_and_last_line(line))
		{
			game->map.map_first_wall = 0;
			return (0);
		}
		game->map.map_first_wall = 1;
		return (1);
	}
	if (!chk_inside_lines(line, game))
		return (0);
	return (len == game->map.max_cols);
}

/*
Validates that a border line contains only '1' characters.
Used for first and last rows which must be entirely walls.
*/
int	chk_first_and_last_line(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

/*
Validates an interior line: must start and end with '1', 
and contain only valid characters.
*/
int	chk_inside_lines(char *line, t_game *game)
{
	int	len;

	len = ft_strlen(line);
	if (len < 2)
		return (0);
	if (line[0] != '1' || line[len - 1] != '1')
		return (0);
	return (validate_chars(line, game, len));
}

int	count_lines(const char *filename)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	line_count = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count - 1);
}
