/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutil_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:04:40 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 09:34:56 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <time.h>

void	find_player_pos(t_game *game);
int		final_map_checks(t_game *game);
int		handle_error(t_game *game, char *line, int fd);
int		initialize_map(const char *file, t_game *game, int *fd,
			int *line_count);
int		read_and_validate_lines(int fd, t_game *game);

/*
Looks for and stores coordinates of player/hero sprite.
*/
void	find_player_pos(t_game *game)
{
	int	y;
	int	x;

	y = 1;
	while (y < game->map.max_rows)
	{
		x = 1;
		while (x < game->map.max_cols)
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'S'
				|| game->map.map[y][x] == 'E' || game->map.map[y][x] == 'W')
			{
				game->map.player_x = x;
				game->map.player_y = y;
				game->curr_x = x;
				game->curr_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

/*
Checks if the map is surrounded by walls and if the herocount
is acceptable.
*/
int	final_map_checks(t_game *game)
{
	if (!check_counts(game))
		return (-1);
	if (!check_map_validity(game))
		return (-1);
	return (0);
}

/*
Handles error cleanup and returns -1.
*/
int	handle_error(t_game *game, char *line, int fd)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	cleanup_early(game);
	return (-1);
}

/*
Initializes the map by counting lines and allocating memory.
*/
int	initialize_map(const char *file, t_game *game, int *fd, int *line_count)
{
	*line_count = count_lines(file);
	if (*line_count < 0 || allocate_map_memory(game, *line_count) < 0)
		return (handle_error(game, NULL, -1));
	*fd = open_map_file(file);
	if (*fd < 0)
		return (handle_error(game, NULL, *fd));
	return (0);
}

/*
Reads and validates each line of the map file using flag-based validation.
Since chk_first_and_last_line handles both first and last line validation
during the line-by-line reading, we don't need separate last line validation.
*/
int	read_and_validate_lines(int fd, t_game *game)
{
	char	*line;
	int		line_num;

	line = NULL;
	line_num = 0;
	while (read_map_line(fd, &line))
	{
		if (validate_and_store_line(line, line_num, game) < 0)
			return (handle_error(game, line, fd));
		line_num++;
		free(line);
		line = NULL;
	}
	game->map.max_rows = line_num;
	game->map.map[line_num] = NULL;
	if (line_num > 0)
	{
		char *last_line = game->map.map[line_num - 1];
		if (chk_first_and_last_line(last_line))
			game->map.map_last_wall = 1;
		else
			game->map.map_last_wall = 0;
	}
	close(fd);
	return (0);
}
