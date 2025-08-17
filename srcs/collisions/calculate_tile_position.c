/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_tile_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:14:43 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 11:18:20 by bleow            ###   ########.fr       */
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
