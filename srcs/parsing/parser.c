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
		if (!in_map)
		{
			int was_map_start = in_map;
			if (is_map_start_line(line, &in_map))
			{
				game->map.map_start_line = pos;
			}
			else if (parse_config_settings(line, game) < 0)
			{
				return (exit_failure_parser(line, fd));
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
	{
		return (-1);
	}
	i = 1; // Initialize debug counter to 1
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
	ft_safefree((void **)&line);
	close(fd);
	return (-1);
}
