/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:02:21 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/07/19 03:05:14 by wjun-kea         ###   ########.fr       */
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
void	initialize_deltas_and_steps(t_ray *ray, t_game *game);

# endif