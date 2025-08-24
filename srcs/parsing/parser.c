/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/25 07:43:34 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <unistd.h>
#include <stdio.h>

/*
Function prototypes
*/
int		parse_map_1(int fd, t_game *game);
int		parse_map_2(int fd, t_game *game);
// int		exit_failure_parser(char *line, int fd);
void	detect_map_start_line(const char *line, int *in_map,
			int *map_start_line, int pos);
int		detect_map_end_line(const char *line, int *in_map,
			int *map_last_line, int pos);
int		parser(const char *file, t_game *game);
int		validate_lines_after_map(int fd);

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
		if (game->map.map_start_line == -1 && in_map < 1)
			detect_map_start_line(line, &in_map, &game->map.map_start_line,
				pos);
		if (detect_map_end_line(line, &in_map, &game->map.map_last_line, pos))
		{
			ft_safefree((void **)&line);
			break ;
		}
		ft_safefree((void **)&line);
		line = get_next_line(fd);
		pos++;
	}
	if (line)
		ft_safefree((void **)&line);
	close (fd);
	return (0);
}

/*
Parse the second pass of the map file, populating map and player info
*/
int	parse_map_2(int fd, t_game *game)
{
	char	*line;
	int		i;

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

int	validate_lines_after_map(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line && i < 2)
	{
		ft_safefree((void **)&line);
		line = get_next_line(fd);
		i++;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_only_whitespace(line))
		{
			ft_safefree((void **)&line);
			return (-1);
		}
		ft_safefree((void **)&line);
		line = get_next_line(fd);
	}
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Cleanup and exit on parser failure
*/
/*
int exit_failure_parser(char *line, int fd) {
    fprintf(stderr, "[DEBUG] Exiting parser due to failure. Cleaning up resources.\n"); // Debug print for cleanup
    ft_safefree((void **)&line);
    close(fd);
    return (-1);
}
*/

void	detect_map_start_line(const char *line, int *in_map,
			int *map_start_line, int pos)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	if (*map_start_line != -1)
		return ;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			has_wall = 1;
		else if (line[i] != ' ')
			return ;
		i++;
	}
	if (has_wall)
	{
		*in_map = 1;
		*map_start_line = pos;
	}
}

int	detect_map_end_line(const char *line, int *in_map, int *map_last_line,
	int pos)
{
	if (*in_map && is_only_whitespace(line))
	{
		*map_last_line = pos - 1;
		return (1);
	}
	return (0);
}

int	open_map_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("Error opening file");
	return (fd);
}

int	parser(const char *file, t_game *game)
{
	int	fd;

	fd = open_map_file(file);
	if (fd < 0)
		return (-1);
	if (parse_map_1(fd, game) < 0)
	{
		close(fd);
		return (-1);
	}
	fd = open_map_file(file);
	if (fd < 0)
		return (-1);
	if (parse_map_2(fd, game) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
