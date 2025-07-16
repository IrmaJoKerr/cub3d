/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 08:39:07 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	open_map_file(const char *file);
int	allocate_map_memory(t_game *game, int line_count);
int	read_map_line(int fd, char **line);
int	validate_and_store_line(char *line, int line_num, t_game *game);
int	parse_map(const char *file, t_game *game);

/*
Opens the .cub map file for reading.
*/
int	open_map_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: \n");
		perror("Error opening file");
	}
	return (fd);
}

/*
Allocates memory for the map based on the number of lines in the file.
*/
int	allocate_map_memory(t_game *game, int line_count)
{
	game->map.max_rows = line_count;
	game->map.map = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!game->map.map)
	{
		perror("Error allocating memory for map");
		return (-1);
	}
	return (0);
}

/*
Get_next_line implementation to read lines from the map file.
*/
int	read_map_line(int fd, char **line)
{
	int	len;

	*line = get_next_line(fd);
	if (!*line)
		return (0);
	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	return (1);
}

/*
Validates each line and copies it to the main map array.
*/
int	validate_and_store_line(char *line, int line_num, t_game *game)
{
	int	len;

	len = ft_strlen(line);
	if (len > game->map.max_cols)
		game->map.max_cols = len;
	if (!validate_line(line, line_num, game))
	{
		ft_fprintf(2, "Invalid map structure.\n");
		return (-1);
	}
	game->map.map[line_num] = ft_strdup(line);
	if (!game->map.map[line_num])
	{
		perror("Error duplicating line");
		return (-1);
	}
	return (0);
}

/*
Main parsing and validation function implementing proper two-pass architecture:
Pass 1: Parse configuration settingss (textures, colors, resolution) until map starts
Pass 2: Calculate map dimensions, allocate memory, and populate map
*/
int	parse_map(const char *file, t_game *game)
{
	int	map_start_line;

	ft_fprintf(2, "Starting two-pass parsing for file: %s\n", file);
	map_start_line = parse_configuration_section(file, game);
	if (map_start_line < 0)
	{
		ft_fprintf(2, "Error: Failed to parse configuration section\n");
		return (-1);
	}
	ft_fprintf(2, "Configuration parsed successfully. Map starts at line %d\n", map_start_line);
	if (parse_map_section(file, game, map_start_line) < 0)
	{
		ft_fprintf(2, "Error: Failed to parse map section\n");
		return (-1);
	}
	ft_fprintf(2, "Two-pass parsing completed successfully\n");
	return (1);
}
