/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:03:54 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/27 05:48:15 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	draw_sky_and_floor(t_game *game, int sky_color, int floor_color);
void	fill_sky_and_floor(t_game *game);
void	render_raycast(t_game *game);
void	draw_crosshair(t_game *game);
int		render_img(t_game *game);

/*
Draw the sky and floor colors for the entire screen.
*/
void	draw_sky_and_floor(t_game *game, int sky_color, int floor_color)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAX_HEIGHT)
	{
		x = 0;
		while (x < MAX_WIDTH)
		{
			if (y < game->midline)
				put_pixel(&game->img, x, y, sky_color);
			else
				put_pixel(&game->img, x, y, floor_color);
			++x;
		}
		++y;
	}
}

/*
Fill the screen with sky and floor colors based on map settings.
*/
void	fill_sky_and_floor(t_game *game)
{
	int	sky_color;
	int	floor_color;

	sky_color = (game->map.sky_color[0] << 16)
		| (game->map.sky_color[1] << 8) | game->map.sky_color[2];
	floor_color = (game->map.floor_color[0] << 16)
		| (game->map.floor_color[1] << 8) | game->map.floor_color[2];
	draw_sky_and_floor(game, sky_color, floor_color);
	render_space_tiles(game);
}

/*
Render the main raycasting view and minimap.
*/
void	render_raycast(t_game *game)
{
	int	x;

	x = 0;
	fill_sky_and_floor(game);
	while (x < MAX_WIDTH)
		render_column(game, x++);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->img.img_ptr, 0, 0);
	render_minimap(game);
}

/*
Draw a crosshair at the center of the screen.
*/
void	draw_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	size;
	int	dx;
	int	dy;

	cx = MAX_WIDTH / 2;
	cy = MAX_HEIGHT / 2;
	size = 10;
	dx = -size;
	while (dx <= size)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, cx + dx, cy, 0xFFFFFF);
		dx++;
	}
	dy = -size;
	while (dy <= size)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, cx, cy + dy, 0xFFFFFF);
		dy++;
	}
}

/*
Render the full frame, including raycast, doors, and crosshair.
*/
int	render_img(t_game *game)
{
	render_raycast(game);
	update_doors(game);
	draw_crosshair(game);
	return (0);
}
