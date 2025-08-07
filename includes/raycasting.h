/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:02:21 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/07 10:43:58 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include "struct.h"

int		render_img(t_game *game);
void	render_column(t_game *game, int x);
void	init_ray(t_ray *ray, t_game *game, int x);
void	put_pixel(t_image *img, int x, int y, int color);
void	fill_sky_and_floor(t_game *game);
t_image	*get_wall_texture(t_game *game, int side, double ray_dir_x, double ray_dir_y);
t_image	*get_surface_texture(t_game *game, t_ray *ray, char hit_tile);
void	initialize_deltas_and_steps(t_ray *ray, t_game *game);

/* Door utility functions */
void	init_doors_from_map(t_game *game);
int		get_door_id(t_game *game, int x, int y);
t_image	*get_door_texture(t_game *game, int door_id, int frame);
t_image	*get_door_side_texture(t_game *game, char door_type, int side, double ray_dir_x, double ray_dir_y);

/* Coordinate conversion functions */
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);

#endif