/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/07 09:29:52 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
Convert tile column index to world X coordinate (left edge of tile)
*/
double	tile_to_world_x(int tile_x)
{
	return ((double)tile_x * TILE_SIZE);
}

/*
Convert tile row index to world Y coordinate (top edge of tile)
*/
double	tile_to_world_y(int tile_y)
{
	return ((double)tile_y * TILE_SIZE);
}

/*
Get world X coordinate of the center of a tile
*/
double	tile_center_x(int tile_x)
{
	return ((double)tile_x * TILE_SIZE + TILE_SIZE / 2.0);
}

/*
Get world Y coordinate of the center of a tile
*/
double	tile_center_y(int tile_y)
{
	return ((double)tile_y * TILE_SIZE + TILE_SIZE / 2.0);
}

/*
Calculate movement delta X for forward/backward movement
*/
double	calc_move_dx(double view_direction, double speed, int forward)
{
	if (forward)
		return (cos(view_direction) * speed);
	else
		return (-cos(view_direction) * speed);
}

/*
Calculate movement delta Y for forward/backward movement
*/
double	calc_move_dy(double view_direction, double speed, int forward)
{
	if (forward)
		return (sin(view_direction) * speed);
	else
		return (-sin(view_direction) * speed);
}

/*
Calculate strafe delta X for left/right movement
*/
double	calc_strafe_dx(double view_direction, double speed, int right)
{
	if (right)
		return (sin(view_direction) * speed);
	else
		return (-sin(view_direction) * speed);
}

/*
Calculate strafe delta Y for left/right movement
*/
double	calc_strafe_dy(double view_direction, double speed, int right)
{
	if (right)
		return (-cos(view_direction) * speed);
	else
		return (cos(view_direction) * speed);
}

/*
Check if a world position is within map bounds
*/
bool	is_within_map_bounds(t_game *game, double x, double y)
{
	int	tile_x;
	int	tile_y;

	tile_x = world_to_tile_x(x);
	tile_y = world_to_tile_y(y);
	
	if (tile_x < 0 || tile_x >= game->map.max_cols || 
		tile_y < 0 || tile_y >= game->map.max_rows)
		return (false);
	
	return (true);
}

/*
Get distance between two world positions
*/
double	calc_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

/*
Normalize angle to 0-2π range
*/
double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

/*
Clamp elevation angle to reasonable range (-π/2 to π/2)
*/
double	clamp_elevation(double elevation)
{
	if (elevation > M_PI / 2)
		return (M_PI / 2);
	if (elevation < -M_PI / 2)
		return (-M_PI / 2);
	return (elevation);
}
