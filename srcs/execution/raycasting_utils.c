/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:22:14 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/27 05:45:40 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	init_ray(t_ray *ray, t_game *game, int x);
void	put_pixel(t_image *img, int x, int y, int color);
t_image	*get_surface_texture(t_game *game, t_ray *ray, char hit_tile);
t_image	*get_wall_texture(t_game *game, int side, double ray_dir_x,
			double ray_dir_y);
void	initialize_deltas_and_steps(t_ray *ray, t_game *game);

/*
Initialize a ray for the given screen column.
*/
void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->cam_x = 2.0 * x / MAX_WIDTH - 1.0;
	ray->dir_x = cos(game->view_direction)
		+ (sin(game->view_direction) * tan(FOV / 2)) * ray->cam_x;
	ray->dir_y = sin(game->view_direction)
		- (cos(game->view_direction) * tan(FOV / 2)) * ray->cam_x;
	ray->map_x = (int)(game->curr_x);
	ray->map_y = (int)(game->curr_y);
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
	initialize_deltas_and_steps(ray, game);
	ray->hit = 0;
}

/*
Set a pixel in the image buffer to the given color.
*/
void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= MAX_WIDTH || y < 0 || y >= MAX_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
Get the texture for the surface hit by the ray (wall or door).
*/
t_image	*get_surface_texture(t_game *game, t_ray *ray, char hit_tile)
{
	int	door_id;

	if (hit_tile == TILE_WALL)
		return (get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y));
	else if (hit_tile == DOOR)
	{
		door_id = get_door_id(game, ray->map_x, ray->map_y);
		if (door_id >= 0)
			return (get_door_texture(game, door_id));
		return (get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y));
	}
	return (game->textures.north_wall);
}

/*
Get the wall texture based on the ray's side and direction.
*/
t_image	*get_wall_texture(t_game *game,
	int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x < 0)
			return (game->textures.west_wall);
		else
			return (game->textures.east_wall);
	}
	else
	{
		if (ray_dir_y < 0)
			return (game->textures.north_wall);
		else
			return (game->textures.south_wall);
	}
}

/*
Initialize DDA step and side distances for the ray.
*/
void	initialize_deltas_and_steps(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->curr_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->curr_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->curr_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->curr_y) * ray->delta_y;
	}
}
