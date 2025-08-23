int exit_failure_parser(char *line, int fd);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 00:47:33 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Function prototypes
*/
int	parse_map_1(const char *file, t_game *game);

/*
Main parsing and validation function implementing proper two-pass architecture:
Pass 1: Parse configuration settings (textures, colors) until map starts
Pass 2: Calculate map dimensions, allocate memory, and populate map
*/
// int	parse_map(const char *file, t_game *game)
// {
// 	int	map_start_line;

// 	fprintf(stderr, "[DEBUG] Entering parse_map for file: %s\n", file);
// 	ft_fprintf(2, "Starting two-pass parsing for file: %s\n", file);
// 	map_start_line = parse_configuration_section(file, game);
// 	fprintf(stderr, "[DEBUG] parse_configuration_section returned: %d\n", map_start_line);
// 	if (map_start_line < 0)
// 	{
// 		fprintf(stderr, "[DEBUG] Error: Failed to parse configuration section\n");
// 		ft_fprintf(2, "Error: \n");
// 		ft_fprintf(2, "Failed to parse configuration section\n");
// 		ft_fprintf(2, "Failed to parse and validate the map.\n");
// 		return (-1);
// 	}
// 	ft_fprintf(2, "Configuration parsed successfully.\nMap starts at line %d\n", map_start_line);
// 	ft_fprintf(2, "Config parsed successfully.\nMap starts at line %d\n",
// 		map_start_line);
// 	fprintf(stderr, "[DEBUG] Calling parse_map_section at line %d\n", map_start_line);
// 	if (parse_map_section(file, game, map_start_line) < 0)
// 	{
// 		fprintf(stderr, "[DEBUG] Error: Failed to parse map section\n");
// 		ft_fprintf(2, "Error: \n");
// 		ft_fprintf(2, "Failed to parse map section\n");
// 		ft_fprintf(2, "Failed to parse and validate the map.\n");
// 		return (-1);
// 	}
// 	fprintf(stderr, "[DEBUG] Two-pass parsing completed successfully\n");
// 	ft_fprintf(2, "Two-pass parsing completed successfully\n");
// 	return (1);
// }

int	parse_map_1(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		in_map;
	int		pos;

	fd = open(file, O_RDONLY);
	in_map = 0;
	pos = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		pos++;
		if (!in_map)
		{
			if (is_map_start_line(line, &in_map))
				game->map.map_start_line = pos;
			else if (parse_config_settings(line, game) < 0)
				return (exit_failure_parser(line, fd));
		}
		if ((in_map) && is_only_whitespace(line))
		{
			game->map.map_last_line = pos - 1;
			ft_safefree((void **)&line);
			break;
		}
	}
	close(fd);
	return (0);
}


int	parse_map_2(const char *file, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	while (i < game->map.map_start_line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
		i++;
	}
	if (calc_map_area(fd, game, i) < 0)
	{
		close(fd);
		return (-1);
	}
	ft_fprintf(2, "Map scan complete: rows=%d, cols=%d, doors=%d, players=%d\n",
		game->map.max_rows, game->map.max_cols, game->doorcount,
		game->map.herocount);
	find_player_position(game);
	close(fd);
	return (0);
}

int	exit_failure_parser(char *line, int fd)
{
	ft_safefree((void **)&line);
	close(fd);
	return (-1);
}
