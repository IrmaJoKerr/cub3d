/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 15:20:59 by bleow            ###   ########.fr       */
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
		ft_printf("Error: \n");
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
	if (line_num == 0)
	{
		game->map.max_cols = ft_strlen(line);
	}
	if (!validate_line(line, line_num, game))
	{
		ft_printf("Invalid map structure.\n");
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
Main parsing and validation function. Controls 10 other
subfunctions in parserutil_a.c and parserutil_b.c to do this.
*/
int	parse_map(const char *file, t_game *game)
{
	int		fd;
	int		line_count;

	if (initialize_map(file, game, &fd, &line_count) < 0)
		return (-1);
	if (read_and_validate_lines(fd, game) < 0)
		return (-1);
	find_hero_position(game);
	if (final_map_checks(game) < 0)
		return (handle_error(game, NULL, -1));
	fprintf(stderr, "DEBUG: Map validation completed successfully.\n");
	ft_printf("Map is valid and ready to load into memory.\n");
	return (1);
}
