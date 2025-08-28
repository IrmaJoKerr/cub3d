/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:07:07 by bleow             #+#    #+#             */
/*   Updated: 2025/08/28 21:48:57 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	copy_tile_to_minimap(t_game *game, t_image *source_tile, int map_x,
			int map_y);
t_image	*set_minitile_type(t_game *game, char tile_type);
void	generate_full_minimap(t_game *game);
void	fill_minimap_pixel(t_game *game, int mapy, int mapx);

/*
Copy a single tile's pixels into the full minimap image at the given
map coordinates.
*/
void	copy_tile_to_minimap(t_game *game, t_image *source_tile,
			int map_x, int map_y)
{
	unsigned int	*full_pixels;
	unsigned int	*tile_pixels;
	int				tile_y;
	int				tile_x;

	if (!source_tile || !source_tile->addr)
		return ;
	if (!game->minimap.full_map_data)
		return ;
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

/*
Return the correct minimap tile image for a given tile type.
*/
t_image	*set_minitile_type(t_game *game, char tile_type)
{
	if (tile_type == TILE_WALL)
		return (game->minimap.wall);
	else if (tile_type == TILE_FLOOR)
		return (game->minimap.floor);
	else if (tile_type == DOOR)
		return (game->minimap.door);
	else if (tile_type == ' ')
		return (game->minimap.space);
	else
		return (game->minimap.floor);
}

/*
Generate the full minimap image by copying all map tiles.
*/
void	generate_full_minimap(t_game *game)
{
	int		map_x;
	int		map_y;
	char	tile_type;
	t_image	*source_tile;

	map_y = 0;
	while (map_y < (game->map.max_rows))
	{
		map_x = 0;
		while ((map_x) < (game->map.max_cols))
		{
			tile_type = game->map.map[map_y][map_x];
			source_tile = set_minitile_type(game, tile_type);
			copy_tile_to_minimap(game, source_tile, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}

/*
Helper function for copy_minimap_pixels. Copies a single pixel
from the full minimap to the minimap viewport.
*/
void	fill_minimap_pixel(t_game *game, int mapy, int mapx)
{
	unsigned int	*f;
	unsigned int	*m;
	int				full_y;
	int				full_x;

	f = (unsigned int *)game->minimap.full_map_data;
	m = (unsigned int *)game->minimap.minimap_data;
	full_y = game->minimap.y + mapy;
	full_x = game->minimap.x + mapx;
	if (full_y >= 0 && full_y < game->minimap.height
		&& full_x >= 0 && full_x < game->minimap.width)
	{
		m[(mapy * (game->minimap.minimap_sl / 4)) + mapx]
			= f[(full_y * (game->minimap.full_map_sl / 4)) + full_x];
	}
	else
		m[(mapy * (game->minimap.minimap_sl / 4)) + mapx] = 0x000000;
}
