/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:02:21 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/28 21:49:17 by bleow            ###   ########.fr       */
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
Door utility functions. In door_utils.c
*/
bool			chk_and_alloc_door_mem(t_game *game);
void			init_doors_from_map(t_game *game);
void			add_door_node(t_game *game, int x, int y, int door_index);
int				get_door_id(t_game *game, int x, int y);
t_image			*get_door_texture(t_game *game, int door_id);

/*
Space tile rendering functions. In draw_space.c
*/
void			draw_space_pixel(t_game *game, t_ray *ray, int x, int y);
void			calc_tex_pixel(t_ray *ray, int *tex_x, int *tex_y);
void			calc_space_ray(t_game *game, t_ray *ray, int x, int y);
unsigned int	sample_texture(t_image *texture, int tex_x, int tex_y);

/*
Minimap player indicator functions. In minimap_draw_player.c
*/
void			calculate_triangle_vertices(t_triangle *tri, t_point center,
					double angle);
void			get_y_bounds(t_triangle tri, int *min_y, int *max_y);
bool			get_scanline_segment(t_triangle tri, int y, int *x_start,
					int *x_end);
void			draw_scanline_segment(t_draw_info info, t_triangle tri, int y,
					int color);
void			rasterize_triangle(t_draw_info info, t_triangle tri);

/*
Minimap setup functions. In minimap_setup.c
*/
int				setup_minimap(t_game *game);
int				alloc_minimap_memory(t_game *game, t_mini *minimap);
int				load_minimap_tiles(t_game *game);
int				load_mini_tex(t_game *game, t_image *tex, char *path);

/*
Minimap utility functions. In minimap_utils.c
*/
void			copy_tile_to_minimap(t_game *game, t_image *source_tile,
					int map_x, int map_y);
t_image			*set_minitile_type(t_game *game, char tile_type);
void			generate_full_minimap(t_game *game);
void			fill_minimap_pixel(t_game *game, int mapy, int mapx);

/*
Minimap functions. In minimap.c
*/
void			render_minimap(t_game *game);
void			calc_minimap_viewport(t_game *game, int *triangle_x,
					int *triangle_y);
void			copy_minimap_pixels(t_game *game);
void			draw_minimap_border(t_game *game);
void			draw_triangle_player_indicator(t_game *game, int center_x,
					int center_y);

/*
Raycasting space floor functions. In raycasting_floor.c				
*/
void			calc_floor_rays(t_rayfloor *rayfloor, t_game *game);
void			calc_floor_projection(t_rayfloor *rayfloor, int y,
					t_game *game);
void			render_tile(t_game *game, int x, int y, t_rayfloor *rayfloor);
bool			is_space_tile(t_game *game, int map_x, int map_y);
void			render_space_tiles(t_game *game);

/*
Raycasting setup functions. In raycasting_setup.c
*/
void			draw_sky_and_floor(t_game *game, int sky_color,
					int floor_color);
void			fill_sky_and_floor(t_game *game);
void			render_raycast(t_game *game);
void			draw_crosshair(t_game *game);
int				render_img(t_game *game);

/*
Raycasting utility functions. In raycasting_utils.c
*/
void			init_ray(t_ray *ray, t_game *game, int x);
void			put_pixel(t_image *img, int x, int y, int color);
t_image			*get_surface_texture(t_game *game, t_ray *ray, char hit_tile);
t_image			*get_wall_texture(t_game *game, int side, double ray_dir_x,
					double ray_dir_y);
void			initialize_deltas_and_steps(t_ray *ray, t_game *game);

/*
Column rendering functions. In render_colum.c
*/
void			compute_projection(t_ray *ray, t_game *game);
void			compute_texture(t_ray *ray, t_game *game, t_image **tex);
void			draw_textured_column(t_game *game, t_ray *ray, t_image *tex,
					int x);
void			render_column(t_game *game, int x);

/*
Door rendering and logic functions. In render_doors.c
*/
void			update_door_state(t_game *game, t_door *door);
void			update_door_animation(t_game *game, t_door *door);
void			update_doors(t_game *game);
bool			check_tile_hit(t_ray *wall_ray, t_ray *door_ray, t_game *game,
					bool *door_found);
void			perform_dda_with_door(t_ray *wall_ray, t_ray *door_ray,
					t_game *game);

#endif