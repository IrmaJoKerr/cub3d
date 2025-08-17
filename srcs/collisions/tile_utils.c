/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:40:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Function prototypes
*/
bool	is_valid_world_position(t_game *game, double x, double y);
void	set_player_to_tile_center(t_game *game, int tile_x, int tile_y);

/*
Check if a world position is valid (not a wall, void, or out of bounds)
*/
bool	is_valid_world_position(t_game *game, double x, double y)
{
	int		tile_x;
	int		tile_y;
	char	tile;

	tile_x = (int)x;
	tile_y = (int)y;
	
	// Bounds checking for safety
	if (tile_x < 0 || tile_x >= game->map.max_cols || 
		tile_y < 0 || tile_y >= game->map.max_rows)
		return (false);
		
	tile = game->map.map[tile_y][tile_x];
	
	// Block walls and void areas (spaces)
	if (tile == TILE_WALL || tile == ' ')
		return (false);
		
	// Allow floors, doors, and player positions
	return (tile == TILE_FLOOR || tile == DOOR || 
		tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W');
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
