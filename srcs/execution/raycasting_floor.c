/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:11:33 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 05:45:33 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	calc_floor_rays(t_rayfloor *rayfloor, t_game *game);
void	calc_floor_projection(t_rayfloor *rayfloor, int y, t_game *game);
void	render_tile(t_game *game, int x, int y, t_rayfloor *rayfloor);
bool	is_space_tile(t_game *game, int map_x, int map_y);
void	render_space_tiles(t_game *game);

/*
Calculate the direction of the floor rays based on the camera 
and view direction.
*/
void	calc_floor_rays(t_rayfloor *rayfloor, t_game *game)
{
	rayfloor->ray_dir_x = cos(game->view_direction)
		+ (sin(game->view_direction) * tan(FOV / 2))
		* rayfloor->cam_x;
	rayfloor->ray_dir_y = sin(game->view_direction)
		- (cos(game->view_direction) * tan(FOV / 2))
		* rayfloor->cam_x;
}

/*
Project the floor ray onto the map and calculate world
coordinates for texture mapping.
*/
void	calc_floor_projection(t_rayfloor *rayfloor, int y, t_game *game)
{
	double	floor_distance;

	floor_distance = (MAX_HEIGHT / 2.0) / (y - game->midline + 1);
	rayfloor->world_x = game->curr_x + floor_distance * rayfloor->ray_dir_x;
	rayfloor->world_y = game->curr_y + floor_distance * rayfloor->ray_dir_y;
	rayfloor->map_x = (int)rayfloor->world_x;
	rayfloor->map_y = (int)rayfloor->world_y;
}

/*
Render a single floor tile using the calculated world
coordinates and texture mapping.
*/
void	render_tile(t_game *game, int x, int y, t_rayfloor *rayfloor)
{
	int		tex_x;
	int		tex_y;
	char	*pixel;

	tex_x = (int)(rayfloor->world_x * TEX_WIDTH) % TEX_WIDTH;
	tex_y = (int)(rayfloor->world_y * TEX_HEIGHT) % TEX_HEIGHT;
	if (!game->textures.space || !game->textures.space->addr)
		return ;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX_WIDTH)
		tex_x = TEX_WIDTH - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= TEX_HEIGHT)
		tex_y = TEX_HEIGHT - 1;
	pixel = game->textures.space->addr
		+ (tex_y * game->textures.space->line_len
			+ tex_x * (game->textures.space->bpp / 8));
	put_pixel(&game->img, x, y, *(unsigned int *)pixel);
}

/*
Check if the given map coordinates correspond to a space tile.
*/
bool	is_space_tile(t_game *game, int map_x, int map_y)
{
	return (map_x >= 0 && map_x < game->map.max_cols
		&& map_y >= 0 && map_y < game->map.max_rows
		&& game->map.map && game->map.map[map_y]
		&& game->map.map[map_y][map_x] == ' ');
}

/*
Render the space tiles for the entire screen.
*/
void	render_space_tiles(t_game *game)
{
	int		y;
	int		x;
	t_ray	ray;

	calc_midline(game);
	if (!game->textures.space || !game->textures.space->addr)
		return ;
	x = 0;
	while (x < MAX_WIDTH)
	{
		y = game->midline;
		while (y < MAX_HEIGHT)
		{
			calc_space_ray(game, &ray, x, y);
			if (is_space_tile(game, ray.map_x, ray.map_y))
				draw_space_pixel(game, &ray, x, y);
			y++;
		}
		x++;
	}
}
