/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:07:07 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 20:38:02 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	copy_tile_to_minimap(t_game *game, t_image *source_tile,
	int map_x, int map_y)
{
	unsigned int	*full_pixels;
	unsigned int	*tile_pixels;
	int				tile_y;
	int				tile_x;

	full_pixels = (unsigned int *)game->minimap.full_map_data;
	tile_pixels = (unsigned int *)source_tile->addr;
	tile_y = 0;
	while (tile_y < 20)
	{
		tile_x = 0;
		while (tile_x < 20)
		{
			full_pixels[((map_y * 20 + tile_y)
					* (game->minimap.full_map_sl / 4)) + (map_x * 20 + tile_x)]
				= tile_pixels[(tile_y * (source_tile->line_len / 4)) + tile_x];
			tile_x++;
		}
		tile_y++;
	}
}

void	generate_full_minimap(t_game *game)
{
	int			map_y;
	int			map_x;
	char		tile_type;
	t_image		*source_tile;

	map_y = 0;
	while (map_y < game->map.max_rows)
	{
		map_x = 0;
		while (map_x < game->map.max_cols)
		{
			tile_type = game->map.map[map_y][map_x];
			if (tile_type == TILE_WALL)
				source_tile = &game->minimap.wall;
			else if (tile_type == TILE_FLOOR)
				source_tile = &game->minimap.floor;
			else if (tile_type == DOOR)
				source_tile = &game->minimap.door;
			else
				source_tile = &game->minimap.floor;
			copy_tile_to_minimap(game, source_tile, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

static void	calc_minimap_viewport(t_game *game,
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
	if (game->minimap.x > game->minimap.full_width - 180)
		game->minimap.x = game->minimap.full_width - 180;
	if (game->minimap.y > game->minimap.full_height - 180)
		game->minimap.y = game->minimap.full_height - 180;
	*triangle_x = (int)(player_pixel_x - game->minimap.x);
	*triangle_y = (int)(player_pixel_y - game->minimap.y);
}

static void	copy_minimap_pixels(t_game *game)
{
	unsigned int	*f;
	unsigned int	*m;
	int				mapy;
	int				mapx;

	f = (unsigned int *)game->minimap.full_map_data;
	m = (unsigned int *)game->minimap.minimap_data;
	mapy = 0;
	while (mapy < 180)
	{
		mapx = 0;
		while (mapx < 180)
		{
			if (game->minimap.y + mapy >= 0
				&& game->minimap.y + mapy < game->minimap.full_height
				&& game->minimap.x + mapx >= 0 && game->minimap.x
				+ mapx < game->minimap.full_width)
				m[(mapy * (game->minimap.minimap_sl / 4)) + mapx]
					= f[((game->minimap.y + mapy)
						* (game->minimap.full_map_sl / 4))
					+ (game->minimap.x + mapx)];
			mapx++;
		}
		mapy++;
	}
}

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
