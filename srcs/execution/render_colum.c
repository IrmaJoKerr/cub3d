/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:47:01 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/23 04:24:30 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

void	compute_projection(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - game->curr_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_dist = (ray->map_y - game->curr_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	ray->line_height = (int)(MAX_HEIGHT / (ray->perp_dist + 1e-6));
	ray->draw_start = fmax(0, -ray->line_height / 2
			+ MAX_HEIGHT / 2 + game->view_elevation);
	ray->draw_end = fmin(MAX_HEIGHT - 1, ray->line_height / 2
			+ MAX_HEIGHT / 2 + game->view_elevation);
}

void	compute_texture(t_ray *ray, t_game *game, t_image **tex)
{
	double	wall_x;

	*tex = get_surface_texture(game, ray, ray->hit_tile);
	if (ray->side == 0)
		wall_x = game->curr_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->curr_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * TEX_WIDTH);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}

void	draw_textured_column(t_game *game, t_ray *ray, t_image *tex, int x)
{
	double			step;
	double			tex_pos;
	int				y;
	char			*pixel;
	unsigned int	color;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - (MAX_HEIGHT / 2
				+ game->view_elevation) + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_pos += step;
		pixel = tex->addr
			+ ((((int)tex_pos) & (TEX_HEIGHT - 1)) * tex->line_len
				+ ray->tex_x * (tex->bpp / 8));
		color = *(unsigned int *)pixel;
		if (color != tex->transparent_color)
			put_pixel(&game->img, x, y, color);
		y++;
	}
}

void	render_column(t_game *game, int x)
{
	t_ray	wall_ray;
	t_ray	door_ray;
	t_image	*tex;

	init_ray(&wall_ray, game, x);
	door_ray.hit = 0;
	perform_dda_with_door(&wall_ray, &door_ray, game);
	compute_projection(&wall_ray, game);
	compute_texture(&wall_ray, game, &tex);
	draw_textured_column(game, &wall_ray, tex, x);
	if (door_ray.hit)
	{
		compute_projection(&door_ray, game);
		compute_texture(&door_ray, game, &tex);
		draw_textured_column(game, &door_ray, tex, x);
	}
}
