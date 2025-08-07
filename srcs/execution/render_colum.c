/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:01:55 by bleow             #+#    #+#             */
/*   Updated: 2025/08/07 16:42:17 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

/* Function to perform the DDA (Digital Differential Analyzer) 
   algorithm to find the first wall hit */

static void	perform_dda(t_ray *ray, t_game *game)
{
	char	tile;

	while (!ray->hit)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		tile = game->map.map[ray->map_y][ray->map_x];
		if (tile == TILE_WALL || tile == HORIZ_DOOR || tile == VERTI_DOOR)
		{
			ray->hit = 1;
			ray->hit_tile = tile;
		}
	}
}

/* Function to compute the projection of the ray onto the screen */

static void	compute_projection(t_ray *ray, t_game *game)
{
	double	curr_tile_x;
	double	curr_tile_y;

	curr_tile_x = game->curr_x / TILE_SIZE;
	curr_tile_y = game->curr_y / TILE_SIZE;
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - curr_tile_x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_dist = (ray->map_y - curr_tile_y
				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
	ray->line_height = (int)(MAX_HEIGHT / (ray->perp_dist + 1e-6));
	
	/* Convert elevation angle to pixel offset */
	int elevation_offset = (int)(tan(game->view_elevation) * (MAX_HEIGHT / 2));
	
	ray->draw_start = fmax(0, -ray->line_height / 2
			+ MAX_HEIGHT / 2 + elevation_offset);
	ray->draw_end = fmin(MAX_HEIGHT - 1, ray->line_height / 2
			+ MAX_HEIGHT / 2 + elevation_offset);
}

/* Function to compute the texture coordinates based on 
   the ray's side and direction */

static void	compute_texture(t_ray *ray, t_game *game, t_image **tex)
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

/* Function to draw a textured column based on the ray's projection and 
   texture */

static void	draw_textured_column(t_game *game, t_ray *ray, t_image *tex, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	char	*pixel;
	int		color;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	
	/* Convert elevation angle to pixel offset for texture positioning */
	int elevation_offset = (int)(tan(game->view_elevation) * (MAX_HEIGHT / 2));
	
	tex_pos = (ray->draw_start - (MAX_HEIGHT / 2
				+ elevation_offset) + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_pos += step;
		pixel = tex->addr + ((((int)tex_pos) & (TEX_HEIGHT - 1))
				* tex->line_len + ray->tex_x * (tex->bpp / 8));
		color = *(unsigned int *)pixel;
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

void	render_column(t_game *game, int x)
{
	t_ray	ray;
	t_image	*tex;

	init_ray(&ray, game, x);
	perform_dda(&ray, game);
	compute_projection(&ray, game);
	compute_texture(&ray, game, &tex);
	draw_textured_column(game, &ray, tex, x);
}
