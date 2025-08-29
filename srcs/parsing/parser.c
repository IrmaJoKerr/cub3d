/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/29 17:32:51 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Function prototypes
*/
int	parser(const char *file, t_game *game);
int	parse_map_1(int fd, t_game *game);
int	parse_map_2(int fd, t_game *game);
int	find_start_line(const char *line, int *in_map, int *map_start_line,
		int pos);
int	find_end_line(const char *line, int *in_map, int *map_last_line,
		int pos);

/*
Controller function that parses the map file
*/
int	parser(const char *file, t_game *game)
{
	int	fd;

	fd = open_map_file(file);
	if (fd < 0)
		return (-1);
	if ((parse_map_1(fd, game) < 0) || (validate_required_config(game) < 0))
	{
		ft_fprintf(2, "Error: Parse_map_1 failed\n");
		close(fd);
		return (-1);
	}
	close (fd);
	fd = open_map_file(file);
	if (fd < 0)
		return (-1);
	if (parse_map_2(fd, game) < 0)
	{
		ft_fprintf(2, "Error: Parse_map_2 failed\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
Parse the first pass of the map file, finding config and map start
*/
int	parse_map_1(int fd, t_game *game)
{
	int		in_map;
	int		pos;
	char	*line;

	in_map = 0;
	pos = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!in_map && parse_config_settings(line, game) < 0)
		{
			ft_safefree((void **)&line);
			return (-1);
		}
		if (find_start_line(line, &in_map, &game->map.map_start_line, pos))
			continue ;
		if (find_end_line(line, &in_map, &game->map.map_last_line, pos))
			break ;
		ft_safefree((void **)&line);
		line = get_next_line(fd);
		pos++;
	}
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Parse the second pass of the map file, populating map and player info
*/
int	parse_map_2(int fd, t_game *game)
{
	char	*line;
	int		i;

	line = NULL;
	i = 1;
	while (i < game->map.map_start_line)
	{
		line = get_next_line(fd);
		if (line)
			ft_safefree((void **)&line);
		i++;
	}
	if (calc_map_area(fd, game, i) < 0)
		return (-1);
	if (game->map.herocount != 1)
	{
		ft_fprintf(2, "Error: Map must have exactly one player (found %d)\n",
			game->map.herocount);
		return (-1);
	}
	if (validate_lines_after_map(fd) < 0)
		return (-1);
	close(fd);
	return (0);
}

/*
Identifies the starting line of the map in the file
*/
int	find_start_line(const char *line, int *in_map, int *map_start_line, int pos)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	if (*map_start_line != -1 || *in_map == 1)
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			has_wall = 1;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	if (has_wall)
	{
		*in_map = 1;
		*map_start_line = pos;
		ft_fprintf(2, "Map start detected at line %d\n", pos);
		return (1);
	}
	return (0);
}

/*
Detects the end of the map in the file.
*/
int	find_end_line(const char *line, int *in_map, int *map_last_line, int pos)
{
	if (*in_map && !is_only_whitespace(line) && ft_strchr(VALID_CHARS, line[0]))
	{
		*map_last_line = pos;
		return (0);
	}
	if (*in_map && is_only_whitespace(line))
	{
		ft_fprintf(2, "Map end detected at line %d\n", *map_last_line);
		return (1);
	}
	return (0);
}
