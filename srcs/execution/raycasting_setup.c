/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 01:03:54 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/17 10:40:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"
#include "../../includes/cub3D.h"

/*
Function prototypes
*/
unsigned int	sample_texture(t_image *texture, int tex_x, int tex_y);
void			render_floor_textures(t_game *game, int midline);
void			draw_sky_and_floor(t_game *game, int sky_color, int floor_color, int midline);
void			fill_sky_and_floor(t_game *game);
void			render_raycast(t_game *game);
void			draw_crosshair(t_game *game);
int				render_img(t_game *game);

unsigned int	sample_texture(t_image *texture, int tex_x, int tex_y)
{
	char	*pixel;

	// Safety check - return black if texture invalid
	if (!texture || !texture->addr)
		return (0x000000);

	// Clamp texture coordinates to valid range
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= TEX_WIDTH) tex_x = TEX_WIDTH - 1;
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= TEX_HEIGHT) tex_y = TEX_HEIGHT - 1;
	
	pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	render_floor_textures(t_game *game, int midline)
{
	int		x, y;
	double	cam_x, ray_dir_x, ray_dir_y;
	double	floor_distance, world_x, world_y;
	int		map_x, map_y, tex_x, tex_y;
	char	tile;
	unsigned int	color;

	// Early exit if space texture not available
	if (!game->textures.space || !game->textures.space->addr)
		return;

	x = 0;
	while (x < MAX_WIDTH)
	{
		cam_x = 2.0 * x / MAX_WIDTH - 1.0;
		ray_dir_x = cos(game->view_direction) + (sin(game->view_direction) * tan(FOV / 2)) * cam_x;
		ray_dir_y = sin(game->view_direction) - (cos(game->view_direction) * tan(FOV / 2)) * cam_x;
		
		y = midline;
		while (y < MAX_HEIGHT)
		{
			floor_distance = (MAX_HEIGHT / 2.0) / (y - midline + 1);
			world_x = game->curr_x + floor_distance * ray_dir_x;
			world_y = game->curr_y + floor_distance * ray_dir_y;
			
			map_x = (int)world_x;
			map_y = (int)world_y;
			
			// Simplified bounds check with early continue
			if (map_x < 0 || map_x >= game->map.max_cols || 
				map_y < 0 || map_y >= game->map.max_rows ||
				!game->map.map || !game->map.map[map_y])
			{
				y++;
				continue;
			}
			
			tile = game->map.map[map_y][map_x];
			if (tile == ' ')
			{
				tex_x = (int)(world_x * TEX_WIDTH) % TEX_WIDTH;
				tex_y = (int)(world_y * TEX_HEIGHT) % TEX_HEIGHT;
				color = sample_texture(game->textures.space, tex_x, tex_y);
				put_pixel(&game->img, x, y, color);
			}
			y++;
		}
		x++;
	}
}

void	draw_sky_and_floor(t_game *game, int sky_color,
	int floor_color, int midline)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAX_HEIGHT)
	{
		x = 0;
		while (x < MAX_WIDTH)
		{
			if (y < midline)
				put_pixel(&game->img, x, y, sky_color);
			else
				put_pixel(&game->img, x, y, floor_color);
			++x;
		}
		++y;
	}
}

void	fill_sky_and_floor(t_game *game)
{
	int	sky_color;
	int	floor_color;
	int	midline;

	sky_color = (game->map.sky_color[0] << 16)
		| (game->map.sky_color[1] << 8) | game->map.sky_color[2];
	floor_color = (game->map.floor_color[0] << 16)
		| (game->map.floor_color[1] << 8) | game->map.floor_color[2];
	midline = MAX_HEIGHT / 2 + game->view_elevation;
	if (midline < 0)
		midline = 0;
	if (midline > MAX_HEIGHT)
		midline = MAX_HEIGHT;
	
	// First fill background colors
	draw_sky_and_floor(game, sky_color, floor_color, midline);
	
	// Then overlay floor textures for space tiles
	render_floor_textures(game, midline);
}

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

int	render_img(t_game *game)
{
	render_raycast(game);
	update_doors(game);
	draw_crosshair(game);
	return (0);
}
