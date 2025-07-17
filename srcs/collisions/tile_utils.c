/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 15:48:31 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Get the tile character at a world position
Returns the character at the tile position, or '1' (wall) if out of bounds
*/
int	get_tile_at_position(t_game *game, double x, double y)
{
	int	tile_x;
	int	tile_y;

	tile_x = world_to_tile_x(x);
	tile_y = world_to_tile_y(y);
	if (tile_x < 0 || tile_x >= game->map.max_cols || 
		tile_y < 0 || tile_y >= game->map.max_rows)
		return (TILE_WALL);
	return (game->map.map[tile_y][tile_x]);
}

/*
Check if a world position is valid (not a wall and within bounds)
*/
bool	is_valid_world_position(t_game *game, double x, double y)
{
	int	tile_char;

	tile_char = get_tile_at_position(game, x, y);
	return (tile_char != TILE_WALL);
}

/*
Set player position to the center of a specific tile
*/
void	set_player_to_tile_center(t_game *game, int tile_x, int tile_y)
{
	game->curr_x = tile_center_x(tile_x);
	game->curr_y = tile_center_y(tile_y);
	game->map.player_x = game->curr_x;
	game->map.player_y = game->curr_y;
}

/*
Get the world X coordinate of the center of a tile
*/
double	get_tile_center_x(int tile_x)
{
	return (tile_center_x(tile_x));
}

/*
Get the world Y coordinate of the center of a tile
*/
double	get_tile_center_y(int tile_y)
{
	return (tile_center_y(tile_y));
}
