/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:07:07 by bleow             #+#    #+#             */
/*   Updated: 2025/08/28 21:48:29 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	render_minimap(t_game *game);
void	calc_minimap_viewport(t_game *game, int *triangle_x, int *triangle_y);
void	copy_minimap_pixels(t_game *game);
void	draw_minimap_border(t_game *game);
void	draw_triangle_player_indicator(t_game *game, int center_x,
			int center_y);

/*
Render the minimap, including border and player indicator, to the window.
*/
void	render_minimap(t_game *game)
{
	int	triangle_x;
	int	triangle_y;

	if (!game->minimap.minimap_img || !game->minimap.full_map_img)
		return ;
	calc_minimap_viewport(game, &triangle_x, &triangle_y);
	copy_minimap_pixels(game);
	draw_minimap_border(game);
	draw_triangle_player_indicator(game, triangle_x, triangle_y);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->minimap.minimap_img, MAX_WIDTH - 190, 10);
}

/*
Calculate the minimap viewport and the position of the player
indicator triangle.
*/
void	calc_minimap_viewport(t_game *game,
	int *triangle_x, int *triangle_y)
{
	double	player_pixel_x;
	double	player_pixel_y;

	player_pixel_x = game->curr_x * 20.0;
	player_pixel_y = game->curr_y * 20.0;
	game->minimap.x = (int)(player_pixel_x - 90.0);
	game->minimap.y = (int)(player_pixel_y - 90.0);
	if (game->minimap.x < 0)
		game->minimap.x = 0;
	if (game->minimap.y < 0)
		game->minimap.y = 0;
	if (game->minimap.x > game->minimap.width - 180)
		game->minimap.x = game->minimap.width - 180;
	if (game->minimap.y > game->minimap.height - 180)
		game->minimap.y = game->minimap.height - 180;
	*triangle_x = (int)(player_pixel_x - game->minimap.x);
	*triangle_y = (int)(player_pixel_y - game->minimap.y);
}

/*
Copy the visible minimap pixels from the full minimap image to the
minimap viewport.
*/
void	copy_minimap_pixels(t_game *game)
{
	int	mapy;
	int	mapx;

	mapy = 0;
	while (mapy < 180)
	{
		mapx = 0;
		while (mapx < 180)
		{
			fill_minimap_pixel(game, mapy, mapx);
			mapx++;
		}
		mapy++;
	}
}

/*
Draw the border around the minimap viewport.
*/
void	draw_minimap_border(t_game *game)
{
	int				x;
	int				y;
	unsigned int	*pixels;

	pixels = (unsigned int *)game->minimap.minimap_data;
	x = 0;
	while (x < 180)
	{
		pixels[(0 * (game->minimap.minimap_sl / 4)) + x] = 0xFFFFFF;
		pixels[(1 * (game->minimap.minimap_sl / 4)) + x] = 0xFFFFFF;
		pixels[(178 * (game->minimap.minimap_sl / 4)) + x] = 0xFFFFFF;
		pixels[(179 * (game->minimap.minimap_sl / 4)) + x] = 0xFFFFFF;
		x++;
	}
	y = 0;
	while (y < 180)
	{
		pixels[(y * (game->minimap.minimap_sl / 4)) + 0] = 0xFFFFFF;
		pixels[(y * (game->minimap.minimap_sl / 4)) + 1] = 0xFFFFFF;
		pixels[(y * (game->minimap.minimap_sl / 4)) + 178] = 0xFFFFFF;
		pixels[(y * (game->minimap.minimap_sl / 4)) + 179] = 0xFFFFFF;
		y++;
	}
}

/*
Draw the player indicator triangle on the minimap.
*/
void	draw_triangle_player_indicator(t_game *game, int center_x, int center_y)
{
	t_triangle	tri;
	t_draw_info	info;
	t_point		center;

	info.pixels = (unsigned int *)game->minimap.minimap_data;
	info.stride = game->minimap.minimap_sl / 4;
	center.x = center_x;
	center.y = center_y;
	calculate_triangle_vertices(&tri, center, game->view_direction);
	rasterize_triangle(info, tri);
}
