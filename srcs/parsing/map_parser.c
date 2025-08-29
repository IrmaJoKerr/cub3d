/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:00:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/29 17:30:19 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		validate_map_line_chars(const char *line, t_game *game,
			int *player_found);
void	set_player_start(t_game *game, char dir);
void	find_player_position(t_game *game);

/*
Validate map line contains only valid characters
*/
int	validate_map_line_chars(const char *line, t_game *game, int *player_found)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr(VALID_CHARS " ", line[i]))
		{
			ft_fprintf(2, "Error: Invalid char '%c' at index %d\n", line[i], i);
			return (-1);
		}
		if (line[i] == 'D')
			game->doorcount++;
		if (ft_strchr("NSEW", line[i]))
		{
			game->map.herocount++;
			if (!(*player_found))
				*player_found = 1;
		}
		i++;
	}
	return (0);
}

/*
Set hero/player start position and direction
*/
void	set_player_start(t_game *game, char dir)
{
	game->curr_x = game->map.player_x + 0.5;
	game->curr_y = game->map.player_y + 0.5;
	game->view_elevation = 0.0;
	if (dir == 'N')
	{
		game->map.start_direction = N;
		game->view_direction = 3 * M_PI / 2;
	}
	else if (dir == 'E')
	{
		game->map.start_direction = E;
		game->view_direction = 0;
	}
	else if (dir == 'S')
	{
		game->map.start_direction = S;
		game->view_direction = M_PI / 2;
	}
	else if (dir == 'W')
	{
		game->map.start_direction = W;
		game->view_direction = M_PI;
	}
}

/*
Find player starting position
*/
void	find_player_position(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (y < game->map.max_rows)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.map[y]))
		{
			if (ft_strchr("NSEW", game->map.map[y][x]))
			{
				game->map.player_x = x;
				game->map.player_y = y;
				set_player_start(game, game->map.map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}
