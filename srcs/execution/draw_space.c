/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:22:36 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 16:58:06 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	draw_space_pixel(t_game *game, t_ray *ray, int x, int y);
void	calc_space_ray(t_game *game, t_ray *ray, int x, int y);
void	prep_img_buffer(t_game *game, t_image *space_img);
t_image	draw_space_buffer(t_game *game);
void	draw_space_row(t_game *game, t_image *space_img, int y);
void	show_space_buffer(t_game *game, t_image *space_img);

/*
Draw a single space tile pixel to the buffer
*/
void	draw_space_pixel(t_game *game, t_ray *ray, int x, int y)
{
	char			*pixel;
	unsigned int	color;
	int				tex_x;
	int				tex_y;

	tex_x = ray->tex_x;
	tex_y = (int)(ray->map_y * TEX_HEIGHT) % TEX_HEIGHT;
	pixel = game->textures.space->addr + (tex_y
			* game->textures.space->line_len + tex_x
			* (game->textures.space->bpp / 8));
	color = *(unsigned int *)pixel;
	color = mlx_get_color_value(game->mlx_ptr, color);
	put_pixel(&game->img, x, y, color);
}

/*
Calculate ray direction and world/tile coordinates for space floor pixel.
*/
void	calc_space_ray(t_game *game, t_ray *ray, int x, int y)
{
	double	floor_distance;
	double	world_x;
	double	world_y;

	ray->cam_x = 2.0 * x / MAX_WIDTH - 1.0;
	ray->dir_x = cos(game->view_direction) + (sin(game->view_direction)
			* tan(FOV / 2)) * ray->cam_x;
	ray->dir_y = sin(game->view_direction) - (cos(game->view_direction)
			* tan(FOV / 2)) * ray->cam_x;
	floor_distance = (MAX_HEIGHT / 2.0) / (y - game->midline + 1);
	world_x = game->curr_x + floor_distance * ray->dir_x;
	world_y = game->curr_y + floor_distance * ray->dir_y;
	ray->map_x = world_to_tile_x(world_x);
	ray->map_y = world_to_tile_y(world_y);
	ray->tex_x = ((int)(world_x * TEX_WIDTH)) % TEX_WIDTH;
}

/*
Create a new image buffer for space floor rendering.
*/
void	prep_img_buffer(t_game *game, t_image *space_img)
{
	space_img->img_ptr = NULL;
	if (!game->textures.space || !game->textures.space->addr)
		return ;
	space_img->img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
	if (!space_img->img_ptr)
		return ;
	space_img->addr = mlx_get_data_addr(space_img->img_ptr, &space_img->bpp,
			&space_img->line_len, &space_img->endian);
}

/*
Draw and fill the space floor tiles in a 2D region below the midline
*/
t_image	draw_space_buffer(t_game *game)
{
	t_image space_img;
	int x;
	int y;
	t_ray ray;

	(void)x;
	(void)ray;
	y = game->midline;
	prep_img_buffer(game, &space_img);
	if (!space_img.img_ptr)
		return (space_img);
	while (y < MAX_HEIGHT)
	{
		draw_space_row(game, &space_img, y);
		y++;
	}
	return (space_img);
}

void	draw_space_row(t_game *game, t_image *space_img, int y)
{
	int		x;
	t_ray	ray;

	(void)space_img;
	x = 0;
	while (x < MAX_WIDTH)
	{
		calc_space_ray(game, &ray, x, y);
		if (ray.map_x < 0 || ray.map_x >= game->map.max_cols || ray.map_y < 0
			|| ray.map_y >= game->map.max_rows || !game->map.map
			|| !game->map.map[ray.map_y])
		{
			x++;
			continue ;
		}
		if (game->map.map[ray.map_y][ray.map_x] == ' ')
			draw_space_pixel(game, &ray, x, y);
		x++;
	}
}

/*
Show and destroy the space tile buffer
*/
void	show_space_buffer(t_game *game, t_image *space_img)
{
	if (!space_img || !space_img->img_ptr)
		return ;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		space_img->img_ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, space_img->img_ptr);
}
