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
void detect_map_start_line(const char *line, int *in_map, int *map_start_line, int pos);
int detect_map_end_line(const char *line, int *in_map, int *map_last_line, int pos);
int parser(const char *file, t_game *game);

/*
Parse the first pass of the map file, finding config and map start
*/
int	parse_map_1(const char *file, t_game *game)
{
	int		fd;
	int		in_map;
	int		pos;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	in_map = 0;
	pos = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (game->map.map_start_line == -1 && in_map < 1)
			detect_map_start_line(line, &in_map, &game->map.map_start_line, pos);
		if (detect_map_end_line(line, &in_map, &game->map.map_last_line, pos))
		{
			ft_safefree((void **)&line);
			break ;
		}
		ft_safefree((void **)&line);
		line = get_next_line(fd);
		pos++;
	}
	ft_safefree((void **)&line);
	close(fd);
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
		return (-1);
	i = 1;
	while (i < game->map.map_start_line)
	{
		line = get_next_line(fd);
		if (line)
			ft_safefree((void **)&line);
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

void	detect_map_start_line(const char *line, int *in_map, int *map_start_line,
	int pos)
{
	if (*map_start_line == -1 && is_map_start_line(line, in_map))
		*map_start_line = pos;
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

int parser(const char *file, t_game *game) {
    if (parse_map_1(file, game) < 0) {
        cleanup_early(game, file);
        return (-1);
    }
    if (parse_map_2(file, game) < 0) {
        cleanup_early(game, file);
        return (-1);
    }
    return (0);
}
