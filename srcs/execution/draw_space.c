/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:22:36 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 04:53:34 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void			draw_space_pixel(t_game *game, t_ray *ray, int x, int y);
void			calc_tex_pixel(t_ray *ray, int *tex_x, int *tex_y);
void			calc_space_ray(t_game *game, t_ray *ray, int x, int y);
unsigned int	sample_texture(t_image *texture, int tex_x, int tex_y);

/*
Draw a single space tile pixel to the buffer
*/
void	draw_space_pixel(t_game *game, t_ray *ray, int x, int y)
{
	char			*pixel;
	unsigned int	color;
	int				tex_x;
	int				tex_y;

	calc_tex_pixel(ray, &tex_x, &tex_y);
	pixel = game->textures.space->addr + (tex_y
			* game->textures.space->line_len + tex_x
			* (game->textures.space->bpp / 8));
	color = *(unsigned int *)pixel;
	color = mlx_get_color_value(game->mlx_ptr, color);
	put_pixel(&game->img, x, y, color);
}

/*
Calculate texture pixel coordinates from world coordinates
*/
void	calc_tex_pixel(t_ray *ray, int *tex_x, int *tex_y)
{
	double	tile_frac_x;
	double	tile_frac_y;

	tile_frac_x = ray->world_x - ray->map_x;
	tile_frac_y = ray->world_y - ray->map_y;
	*tex_x = (int)(tile_frac_x * TEX_WIDTH);
	*tex_y = (int)(tile_frac_y * TEX_HEIGHT);
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= TEX_WIDTH)
		*tex_x = TEX_WIDTH - 1;
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= TEX_HEIGHT)
		*tex_y = TEX_HEIGHT - 1;
}

/*
Calculate ray direction and world/tile coordinates for space floor pixel.
*/
void	calc_space_ray(t_game *game, t_ray *ray, int x, int y)
{
	double	floor_distance;

	ray->cam_x = 2.0 * x / MAX_WIDTH - 1.0;
	ray->dir_x = cos(game->view_direction) + (sin(game->view_direction)
			* tan(FOV / 2)) * ray->cam_x;
	ray->dir_y = sin(game->view_direction) - (cos(game->view_direction)
			* tan(FOV / 2)) * ray->cam_x;
	floor_distance = (MAX_HEIGHT / 2.0) / (y - game->midline + 1);
	ray->world_x = game->curr_x + floor_distance * ray->dir_x;
	ray->world_y = game->curr_y + floor_distance * ray->dir_y;
	ray->map_x = (int)ray->world_x;
	ray->map_y = (int)ray->world_y;
	ray->tex_x = ((int)(ray->world_x * TEX_WIDTH)) % TEX_WIDTH;
}

/*
Sample a pixel color from a texture at given coordinates
*/
unsigned int	sample_texture(t_image *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (!texture || !texture->addr)
		return (0x000000);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX_WIDTH)
		tex_x = TEX_WIDTH - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= TEX_HEIGHT)
		tex_y = TEX_HEIGHT - 1;
	pixel = texture->addr + (tex_y * texture->line_len + tex_x
			* (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}
