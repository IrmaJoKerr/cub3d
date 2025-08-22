/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:07:07 by bleow             #+#    #+#             */
/*   Updated: 2025/08/21 13:57:30 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	setup_minimap(t_game *game)
{
	if (!game || !game->mlx_ptr)
		return ;
	game->minimap.full_pixel_width = game->map.max_cols * 20;
	game->minimap.full_pixel_height = game->map.max_rows * 20;
	load_minimap_tiles(game);
	game->minimap.full_map_img = mlx_new_image(game->mlx_ptr,
			game->minimap.full_pixel_width, game->minimap.full_pixel_height);
	if (!game->minimap.full_map_img)
		return ;
	game->minimap.full_map_data = mlx_get_data_addr(game->minimap.full_map_img,
			&game->minimap.full_map_bpp, &game->minimap.full_map_sl,
			&game->minimap.full_map_endian);
	generate_full_minimap(game);
	game->minimap.minimap_img = mlx_new_image(game->mlx_ptr, 180, 180);
	if (!game->minimap.minimap_img)
		return ;
	game->minimap.minimap_data = mlx_get_data_addr(game->minimap.minimap_img,
			&game->minimap.minimap_bpp, &game->minimap.minimap_sl,
			&game->minimap.minimap_endian);
}

void	load_minimap_tiles(t_game *game)
{
	int	tile_width;
	int	tile_height;

	game->minimap.wall.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/minimap/wall.xpm", &tile_width, &tile_height);
	if (!game->minimap.wall.img_ptr)
		return ;
	game->minimap.wall.addr = mlx_get_data_addr(game->minimap.wall.img_ptr,
			&game->minimap.wall.bpp, &game->minimap.wall.line_len,
			&game->minimap.wall.endian);
	game->minimap.floor.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/minimap/floor.xpm", &tile_width, &tile_height);
	if (!game->minimap.floor.img_ptr)
		return ;
	game->minimap.floor.addr = mlx_get_data_addr(game->minimap.floor.img_ptr,
			&game->minimap.floor.bpp, &game->minimap.floor.line_len,
			&game->minimap.floor.endian);
	game->minimap.door.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/minimap/door.xpm", &tile_width, &tile_height);
	if (!game->minimap.door.img_ptr)
		return ;
	game->minimap.door.addr = mlx_get_data_addr(game->minimap.door.img_ptr,
			&game->minimap.door.bpp, &game->minimap.door.line_len,
			&game->minimap.door.endian);
}

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
