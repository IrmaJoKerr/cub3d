/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_tile_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:14:43 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 03:46:54 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);
bool	is_valid_move(t_game *game, double x, double y);

/*
Convert world X coordinate to tile column index
*/
int	world_to_tile_x(double x)
{
	return ((int)(x / TILE_SIZE));
}

/*
Convert world Y coordinate to tile row index
*/
int	world_to_tile_y(double y)
{
	return ((int)(y / TILE_SIZE));
}

/*
Check if a world position is valid (not a wall, void, or out of bounds)
*/
bool	is_valid_move(t_game *game, double x, double y)
{
	int		tile_x;
	int		tile_y;
	char	tile;

	tile_x = (int)x;
	tile_y = (int)y;
	if (tile_x < 0 || tile_x >= game->map.max_cols
		|| tile_y < 0 || tile_y >= game->map.max_rows)
		return (false);
	tile = game->map.map[tile_y][tile_x];
	if (tile == TILE_WALL || tile == ' ')
		return (false);
	return (tile == TILE_FLOOR || tile == DOOR
		|| tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W');
}
