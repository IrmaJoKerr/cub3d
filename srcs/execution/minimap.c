/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:07:07 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:22:07 by bleow            ###   ########.fr       */
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
	usleep(500000);
	generate_full_minimap(game);
	game->minimap.minimap_img = mlx_new_image(game->mlx_ptr, 180, 180);
	if (!game->minimap.minimap_img)
		return ;
	game->minimap.minimap_data = mlx_get_data_addr(game->minimap.minimap_img,
			&game->minimap.minimap_bpp, &game->minimap.minimap_sl,
			&game->minimap.minimap_endian);
	usleep(1000);
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
	game->minimap.space.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/minimap/space.xpm", &tile_width, &tile_height);
	if (!game->minimap.space.img_ptr)
		return ;
	game->minimap.space.addr = mlx_get_data_addr(game->minimap.space.img_ptr,
			&game->minimap.space.bpp, &game->minimap.space.line_len,
			&game->minimap.space.endian);
}

void	generate_full_minimap(t_game *game)
{
	int				map_y;
	int				map_x;
	int				tile_y;
	int				tile_x;
	char			tile_type;
	t_image			*source_tile;
	unsigned int	*full_pixels;
	unsigned int	*tile_pixels;

	full_pixels = (unsigned int *)game->minimap.full_map_data;
	map_y = 0;
	while (map_y < game->map.max_rows && game->map.map[map_y])
	{
		map_x = 0;
		while (map_x < game->map.max_cols && game->map.map[map_y])
		{
			tile_type = game->map.map[map_y][map_x];
			if (tile_type == TILE_WALL)
				source_tile = &game->minimap.wall;
			else if (tile_type == TILE_FLOOR)
				source_tile = &game->minimap.floor;
			else if (tile_type == DOOR)
				source_tile = &game->minimap.door;
			else if (tile_type == ' ')
				source_tile = &game->minimap.space;
			else
				source_tile = &game->minimap.floor;
			tile_pixels = (unsigned int *)source_tile->addr;
			tile_y = 0;
			while (tile_y < 20)
			{
				tile_x = 0;
				while (tile_x < 20)
				{
					full_pixels[((map_y * 20 + tile_y) * (game->minimap.full_map_sl / 4)) + (map_x * 20 + tile_x)] = 
						tile_pixels[(tile_y * (source_tile->line_len / 4)) + tile_x];
					tile_x++;
				}
				tile_y++;
			}
			map_x++;
		}
		map_y++;
	}
}

void	render_minimap(t_game *game)
{
	double			player_pixel_x;
	double			player_pixel_y;
	int				triangle_x;
	int				triangle_y;
	int				minimap_y;
	int				minimap_x;
	unsigned int	*full_pixels;
	unsigned int	*minimap_pixels;

	if (!game->minimap.minimap_img || !game->minimap.full_map_img)
		return ;
	
	// Check if data pointers are valid - COMMENTED OUT FOR TESTING
	// if (!game->minimap.full_map_data || !game->minimap.minimap_data)
	//	return ;
	
	// Convert player tile coordinates to minimap pixel coordinates
	// curr_x and curr_y are in tile coordinates (e.g., 9.5, 5.5)
	// Each tile is 20 pixels in the minimap
	player_pixel_x = game->curr_x * 20.0;
	player_pixel_y = game->curr_y * 20.0;
	
	// Calculate viewport extraction area (center 180x180 on player - continuous)
	game->minimap.src_start_x = (int)(player_pixel_x - 90.0);
	game->minimap.src_start_y = (int)(player_pixel_y - 90.0);
	
	// Clamp to full map boundaries
	if (game->minimap.src_start_x < 0)
		game->minimap.src_start_x = 0;
	if (game->minimap.src_start_y < 0)
		game->minimap.src_start_y = 0;
	if (game->minimap.src_start_x > game->minimap.full_pixel_width - 180)
		game->minimap.src_start_x = game->minimap.full_pixel_width - 180;
	if (game->minimap.src_start_y > game->minimap.full_pixel_height - 180)
		game->minimap.src_start_y = game->minimap.full_pixel_height - 180;
	
	// Calculate triangle position relative to viewport (continuous)
	triangle_x = (int)(player_pixel_x - game->minimap.src_start_x);
	triangle_y = (int)(player_pixel_y - game->minimap.src_start_y);
	
	// Copy viewport area from full map to minimap
	full_pixels = (unsigned int *)game->minimap.full_map_data;
	minimap_pixels = (unsigned int *)game->minimap.minimap_data;
	minimap_y = 0;
	while (minimap_y < 180)
	{
		minimap_x = 0;
		while (minimap_x < 180)
		{
			// Add bounds checking to prevent buffer overflow
			int full_y = game->minimap.src_start_y + minimap_y;
			int full_x = game->minimap.src_start_x + minimap_x;
			
			// Ensure we don't access beyond full map boundaries
			if (full_y >= 0 && full_y < game->minimap.full_pixel_height && 
				full_x >= 0 && full_x < game->minimap.full_pixel_width)
			{
				minimap_pixels[(minimap_y * (game->minimap.minimap_sl / 4)) + minimap_x] = 
					full_pixels[(full_y * (game->minimap.full_map_sl / 4)) + full_x];
			}
			else
			{
				// Fill with black for out-of-bounds areas
				minimap_pixels[(minimap_y * (game->minimap.minimap_sl / 4)) + minimap_x] = 0x000000;
			}
			minimap_x++;
		}
		minimap_y++;
	}
	draw_minimap_border(game);
	draw_triangle_player_indicator(game, triangle_x, triangle_y);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->minimap.minimap_img, MAX_WIDTH - 190, 10);
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
	int				tip_x, tip_y, base_left_x, base_left_y, base_right_x, base_right_y;
	int				min_y, max_y, y, x_start, x_end, stride;
	unsigned int	*pixels;

	pixels = (unsigned int *)game->minimap.minimap_data;
	stride = game->minimap.minimap_sl / 4;  // Pre-calculate stride

	// Pre-calculate trigonometric values (±1° accuracy is sufficient)
	int cos_val = (int)(cos(game->view_direction) * 6.0);
	int sin_val = (int)(sin(game->view_direction) * 6.0);
	int cos_left = (int)(cos(game->view_direction + 2.531) * 6.0);   // 145° (5° wider)
	int sin_left = (int)(sin(game->view_direction + 2.531) * 6.0);
	int cos_right = (int)(cos(game->view_direction - 2.531) * 6.0);  // -145° (5° wider)
	int sin_right = (int)(sin(game->view_direction - 2.531) * 6.0);

	// Calculate triangle vertices
	tip_x = center_x + cos_val;
	tip_y = center_y + sin_val;
	base_left_x = center_x + cos_left;
	base_left_y = center_y + sin_left;
	base_right_x = center_x + cos_right;
	base_right_y = center_y + sin_right;

	// Calculate exact bounding box (much smaller than 15x15)
	min_y = tip_y;
	if (base_left_y < min_y) min_y = base_left_y;
	if (base_right_y < min_y) min_y = base_right_y;
	max_y = tip_y;
	if (base_left_y > max_y) max_y = base_left_y;
	if (base_right_y > max_y) max_y = base_right_y;

	// Clamp to minimap bounds
	if (min_y < 0) min_y = 0;
	if (max_y >= 180) max_y = 179;

	// Scanline fill - optimized triangle rasterization
	y = min_y;
	while (y <= max_y)
	{
		// Find intersection points with triangle edges for this scanline
		x_start = 180;  // Start with impossible values
		x_end = -1;
		
		// Edge 1: tip to base_left
		if ((tip_y <= y && y <= base_left_y) || (base_left_y <= y && y <= tip_y))
		{
			if (tip_y != base_left_y)
			{
				int x_intersect = tip_x + ((base_left_x - tip_x) * (y - tip_y)) / (base_left_y - tip_y);
				if (x_intersect < x_start) x_start = x_intersect;
				if (x_intersect > x_end) x_end = x_intersect;
			}
		}
		
		// Edge 2: base_left to base_right
		if ((base_left_y <= y && y <= base_right_y) || (base_right_y <= y && y <= base_left_y))
		{
			if (base_left_y != base_right_y)
			{
				int x_intersect = base_left_x + ((base_right_x - base_left_x) * (y - base_left_y)) / (base_right_y - base_left_y);
				if (x_intersect < x_start) x_start = x_intersect;
				if (x_intersect > x_end) x_end = x_intersect;
			}
		}
		
		// Edge 3: base_right to tip
		if ((base_right_y <= y && y <= tip_y) || (tip_y <= y && y <= base_right_y))
		{
			if (base_right_y != tip_y)
			{
				int x_intersect = base_right_x + ((tip_x - base_right_x) * (y - base_right_y)) / (tip_y - base_right_y);
				if (x_intersect < x_start) x_start = x_intersect;
				if (x_intersect > x_end) x_end = x_intersect;
			}
		}
		
		// Fill horizontal line between intersection points
		if (x_start <= x_end && x_start < 180 && x_end >= 0)
		{
			int x;
			
			if (x_start < 0) x_start = 0;
			if (x_end >= 180) x_end = 179;
			
			// Fast horizontal line fill using pre-calculated stride
			x = x_start;
			while (x <= x_end)
			{
				pixels[y * stride + x] = 0xFF4500; // Orange arrowhead
				x++;
			}
		}
		y++;
	}
}
