/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:49:53 by bleow             #+#    #+#             */
/*   Updated: 2025/08/29 17:32:27 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Function prototypes
*/
int	open_map_file(const char *file);
int	validate_lines_after_map(int fd);
int	calc_map_area(int fd, t_game *game, int i);
int	check_valid_file_path(char *path);

/*
Open the map file for reading.
Returns the file descriptor on success, -1 on failure.
*/
int	open_map_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: failed to open file: %s\n", file);
		return (-1);
	}
	return (fd);
}

/*
Validate lines after the map to ensure no invalid content
*/
int	validate_lines_after_map(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (i >= 2 && !is_only_whitespace(line))
		{
			ft_safefree((void **)&line);
			ft_fprintf(2, "Error: Invalid line after map detected\n");
			return (-1);
		}
		ft_safefree((void **)&line);
		line = get_next_line(fd);
		i++;
	}
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Calculate map dimensions and validate map characters
Starting from map_start_line, read until EOF
*/
int	calc_map_area(int fd, t_game *game, int i)
{
	char	*line;
	int		player_found;

	player_found = 0;
	line = NULL;
	game->map.max_rows = ((game->map.map_last_line - game->map.map_start_line)
			+ 1);
	while (i <= game->map.map_last_line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)ft_strlen(line) > game->map.max_cols)
			game->map.max_cols = (int)ft_strlen(line);
		if (validate_map_line_chars(line, game, &player_found) < 0)
		{
			ft_safefree((void **)&line);
			return (-1);
		}
		ft_safefree((void **)&line);
		i++;
	}
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Check if a file path is valid and accessible
*/
int	check_valid_file_path(char *path)
{
	int	fd;

	if (!path || ft_strlen(path) == 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: Cannot access file: %s\n", path);
		return (0);
	}
	close(fd);
	return (1);
}
