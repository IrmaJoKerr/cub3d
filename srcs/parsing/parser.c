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
int	parse_map_2(const char *file, t_game *game);
int	exit_failure_parser(char *line, int fd);

/*
Parse the first pass of the map file, finding config and map start
*/
int	parse_map_1(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		in_map;
	int		pos;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	in_map = 0;
	pos = 1; // Start line counter from 1
	line = get_next_line(fd);
	while (line != NULL)
	{
		fprintf(stderr, "[DEBUG] Line %d: %s", pos, line); // Debug print for each line read
		fprintf(stderr, "[DEBUG] Current line number: %d, in_map: %d\n", pos, in_map);
		fprintf(stderr, "[DEBUG] Processing line %d: '%s'\n", pos, line);
		if (game->map.map_start_line == -1)
		{
			if (is_map_start_line(line, &in_map))
			{
				game->map.map_start_line = pos;
				fprintf(stderr, "[DEBUG] Map start identified at line %d\n", pos);
			}
			else
			{
				fprintf(stderr, "[DEBUG] Line %d is not the start of the map\n", pos);
			}
		}
		if (in_map && is_only_whitespace(line))
		{
			game->map.map_last_line = pos - 1;
			ft_safefree((void **)&line);
			break;
		}
		ft_safefree((void **)&line);
		line = get_next_line(fd);
		pos++;
	}
	// Adjust map_start_line to skip to the line before
	if (game->map.map_start_line > 1)
	{
		game->map.map_start_line--;
	}
	ft_safefree((void **)&line);
	close(fd);
	fprintf(stderr, "[DEBUG] parse_map_1 succeeded. Map start line: %d, Map last line: %d\n", game->map.map_start_line, game->map.map_last_line);
	return (0);
}


/*
Parse the second pass of the map file, populating map and player info
*/
int	parse_map_2(const char *file, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	i = 1; // Initialize debug counter to 1
	fprintf(stderr, "[DEBUG] Starting parse_map_2. Map start line: %d\n", game->map.map_start_line);
	while (i < game->map.map_start_line)
	{
		line = get_next_line(fd);
		if (line)
		{
			fprintf(stderr, "[DEBUG] Skipping Line %d: %s", i, line); // Debug print for skipped lines
			ft_safefree((void **)&line);
		}
		i++;
	}
	if (calc_map_area(fd, game, i) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
Cleanup and exit on parser failure
*/
int	exit_failure_parser(char *line, int fd)
{
	fprintf(stderr, "[DEBUG] Exiting parser due to failure. Cleaning up resources.\n"); // Debug print for cleanup
	ft_safefree((void **)&line);
	close(fd);
	return (-1);
}
