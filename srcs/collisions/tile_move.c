/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:40:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);
double	tile_center_x(int tile_x);
double	tile_center_y(int tile_y);
double	calc_move_dx(double view_direction, double speed, int forward);
double	calc_move_dy(double view_direction, double speed, int forward);
double	calc_strafe_dx(double view_direction, double speed, int right);
double	calc_strafe_dy(double view_direction, double speed, int right);
double	calc_distance(double x1, double y1, double x2, double y2);
double	normalize_angle(double angle);
double	clamp_elevation(double elevation);

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
	if (elevation > 289)
		return (289);
	if (elevation < -289)
		return (-289);
	return (elevation);
}
