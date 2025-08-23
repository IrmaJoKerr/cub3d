/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:02:21 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/23 17:44:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "struct.h"
# include "cub3D.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdbool.h>

/*
Raycasting setup functions. In raycasting_setup.c
*/
void	draw_sky_and_floor(t_game *game, int sky_color, int floor_color);
void	fill_sky_and_floor(t_game *game);
void	render_raycast(t_game *game);
void	draw_crosshair(t_game *game);
int		render_img(t_game *game);

/*
Raycasting utility functions. In raycasting_utils.c
*/
void	init_ray(t_ray *ray, t_game *game, int x);
void	put_pixel(t_image *img, int x, int y, int color);
t_image	*get_surface_texture(t_game *game, t_ray *ray, char hit_tile);
t_image	*get_wall_texture(t_game *game, int side, double ray_dir_x,
			double ray_dir_y);
void	initialize_deltas_and_steps(t_ray *ray, t_game *game);

/*
Column rendering functions. In render_colum.c
*/
void	compute_projection(t_ray *ray, t_game *game);
void	compute_texture(t_ray *ray, t_game *game, t_image **tex);
void	draw_textured_column(t_game *game, t_ray *ray, t_image *tex, int x);
void	render_column(t_game *game, int x);

/*
Door rendering and logic functions. In render_doors.c
*/
void	update_door_state(t_game *game, t_door *door);
void	update_door_animation(t_game *game, t_door *door);
void	update_doors(t_game *game);
bool	check_tile_hit(t_ray *wall_ray, t_ray *door_ray, t_game *game,
			bool *door_found);
void	perform_dda_with_door(t_ray *wall_ray, t_ray *door_ray, t_game *game);

/*
Space floor rendering functions. In draw_space.c
*/
void	draw_space_pixel(t_game *game, t_ray *ray, int x, int y);
void	calc_space_ray(t_game *game, t_ray *ray, int x, int y);
void	prep_img_buffer(t_game *game, t_image *space_img);
t_image	draw_space_buffer(t_game *game);
void	draw_space_row(t_game *game, t_image *space_img, int y);
void	show_space_buffer(t_game *game, t_image *space_img);

/*
Door utility functions. In door_utils.c
*/
void	init_doors_from_map(t_game *game);
int		get_door_id(t_game *game, int x, int y);
t_image	*get_door_texture(t_game *game, int door_id);
void	cleanup_door_frames(t_game *game);

/*
Minimap functions. In minimap.c
*/
void	setup_minimap(t_game *game);
void	load_minimap_tiles(t_game *game);
void	draw_minimap_border(t_game *game);
void	draw_triangle_player_indicator(t_game *game, int center_x,
			int center_y);

/*
Minimap utility functions. In minimap_utils.c
*/
void	copy_tile_to_minimap(t_game *game, t_image *source_tile, int map_x,
			int map_y);
void	generate_full_minimap(t_game *game);
void	calc_minimap_viewport(t_game *game, int *triangle_x, int *triangle_y);
void	copy_minimap_pixels(t_game *game);
void	render_minimap(t_game *game);

/*
Minimap player indicator functions. In minimap_draw_player.c
*/
void	calculate_triangle_vertices(t_triangle *tri, t_point center,
			double angle);
void	rasterize_triangle(t_draw_info info, t_triangle tri);

#endif