/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/12 23:22:43 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Check if a world position is valid (not a wall and within bounds)
*/
bool	is_valid_world_position(t_game *game, double x, double y)
{
	if (game->map.map[(int)y][(int)x] == TILE_WALL)
		return (false);
	return (true);
}

/*
Set player position to the center of a specific tile
*/
void	set_player_to_tile_center(t_game *game, int tile_x, int tile_y)
{
	game->curr_x = tile_x + 0.5;
	game->curr_y = tile_y + 0.5;
	game->map.player_x = game->curr_x;
	game->map.player_y = game->curr_y;
}
