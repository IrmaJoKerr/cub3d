/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/07 16:50:35 by bleow            ###   ########.fr       */
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
Check if a door at given tile coordinates blocks movement
*/
bool	is_door_closed(t_game *game, int tile_x, int tile_y)
{
	char	tile;
	int		door_id;
	
	tile = game->map.map[tile_y][tile_x];
	if (tile == HORIZ_DOOR || tile == VERTI_DOOR)
	{
		door_id = get_door_id(game, tile_x, tile_y);
		if (door_id >= 0)
		{
			// Block movement if door is not fully OPEN, OR if player is attempting entry during animation
			if (game->doors[door_id].state != DOOR_OPEN)
				return (true);
			
			if (is_player_attempting_entry(game, &game->doors[door_id]) && 
				(game->doors[door_id].state == DOOR_OPENING || game->doors[door_id].state == DOOR_CLOSING))
				return (true);
		}
	}
	return (false);
}

/*
Enhanced collision detection with simplified variables using constant margin
*/
bool	is_valid_world_position(t_game *game, double x, double y)
{
	int		check_tiles[4][2];
	int		i;
	char	tile_char;

	// Direct calculation using constant margin - no unnecessary variables
	check_tiles[0][0] = (int)((x / TILE_SIZE) - COLL_MARGIN);  // Top-left X
	check_tiles[0][1] = (int)((y / TILE_SIZE) - COLL_MARGIN);  // Top-left Y
	check_tiles[1][0] = (int)((x / TILE_SIZE) + COLL_MARGIN);  // Top-right X
	check_tiles[1][1] = (int)((y / TILE_SIZE) - COLL_MARGIN);  // Top-right Y
	check_tiles[2][0] = (int)((x / TILE_SIZE) - COLL_MARGIN);  // Bottom-left X
	check_tiles[2][1] = (int)((y / TILE_SIZE) + COLL_MARGIN);  // Bottom-left Y
	check_tiles[3][0] = (int)((x / TILE_SIZE) + COLL_MARGIN);  // Bottom-right X
	check_tiles[3][1] = (int)((y / TILE_SIZE) + COLL_MARGIN);  // Bottom-right Y
	
	i = 0;
	while (i < 4)
	{
		if (check_tiles[i][0] < 0 || check_tiles[i][0] >= game->map.max_cols ||
			check_tiles[i][1] < 0 || check_tiles[i][1] >= game->map.max_rows)
			return (false);
		
		tile_char = game->map.map[check_tiles[i][1]][check_tiles[i][0]];
		if (tile_char == TILE_WALL || is_door_closed(game, check_tiles[i][0], check_tiles[i][1]))
			return (false);
		
		i++;
	}
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
