/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:11:34 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# include "raycasting.h"

/*
Main functions. In cub3D.c
*/
void	init_game(t_game *game, const char *map_file);
char	*get_map_path(const char *map_file);
int		check_valid_file_path(const char *path);
void	load_texture(t_game *game, t_image *tex, char *path);
void	load_all_door_textures(t_game *game);
int		count_door_textures(void);

/*
Cleanup functions a. In cleanup_a.c
*/
void	cleanup(t_game *game);
int		close_window(t_game *game);
void	cleanup_early(t_game *game);
void	cleanup_later(t_game *game);

/*
Cleanup functions b. In cleanup_b.c
*/
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_mlx_textures(t_game *game);
void	cleanup_mlx_system(t_game *game);
// void	cleanup_single_map(char ***map_ptr);     // OBSOLETE - Defined but never called
void	clean_wall_textures(t_game *game);

/*
Map utility functions. In map_utils.c
*/
char	**copy_map_array(char **source_map, int rows);

/*
Initialization functions. In initstructs.c
*/
void	init_game_st(t_game *game);
void	init_texture_st(t_texture *texture);
void	init_map_st(t_map *map);
void	alloc_and_init_all(t_game **game);

/*
Map validation functions. In map_validation.c
*/
int		is_valid_path(t_game *game, int y, int x);
int		flood_fill_validate(t_game *game, char **test_map, int y, int x);
int		is_reachable_space(char c);

/*
Tile coordinate utility functions. In collisions/tile_utils.c
*/
bool	is_valid_world_position(t_game *game, double x, double y);
void	set_player_to_tile_center(t_game *game, int tile_x, int tile_y);

/*
Tile movement calculation functions. In collisions/tile_move.c
*/
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);
double	tile_center_x(int tile_x);
double	tile_center_y(int tile_y);
double	calc_move_dx(double view_direction, double speed, int forward);
double	calc_move_dy(double view_direction, double speed, int forward);
double	calc_strafe_dx(double view_direction, double speed, int right);
double	calc_strafe_dy(double view_direction, double speed, int right);
double	calc_distance(double x1, double y1, double x2, double y2);
double	normalize_angle(double angle);
double	clamp_elevation(double elevation);

/*
Door animation utility functions. In door_utils.c
*/
void	cleanup_door_frames(t_game *game);

/*
Path parsing functions. In parse_path.c
*/
void	chk_args(int argc, char **argv);
int		validate_xmp_extension(const char *path);
int		check_valid_texture_path(const char *path);

/*
Parser functions. In parser.c
*/
int		parse_map(const char *file, t_game *game);

/*
Configuration parser functions. In config_parser.c
*/
int		parse_configuration_section(const char *file, t_game *game);
int		is_only_whitespace(const char *line);
int		is_map_start_line(const char *line);
int		parse_config_settings(char *line, t_game *game);
int		handle_texture_settings(char *line, t_game *game, int settings_type);
int		handle_color_settings(char *line, t_game *game, int settings_type);
int		validate_required_config(t_game *game);
int		cleanup_and_return(int fd, char *line, int ret_val);

/*
Parser helper functions. In parser_helpers.c
*/
int		identify_settings_type(const char *line);
char	*extract_texture_path(const char *line, const char *identifier);
int		parse_color_settings(char *line, t_game *game, char settings);
char	*extract_color_values(const char *line, const char *identifier);
int		validate_color_values(const char *values, int color[3]);

/*
Map parser functions. In map_parser.c
*/
int		parse_map_section(const char *file, t_game *game, int map_start_line);
int		calculate_map_dimensions(const char *file, t_game *game, int map_start_line);
int		validate_map_line_chars(const char *line);
int		validate_border_line(const char *line);
int		populate_map_array(const char *file, t_game *game, int map_start_line);
void	count_player_chars(const char *line, t_game *game);
int		validate_interior_line(const char *line);
void	find_player_position(t_game *game);
int		final_map_validation(t_game *game);

/*
Debug functions. In debug.c
*/
void	debug_print_map(t_game *game);

/*
Key hook functions. In keyhooks_a.c
*/
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_window_close(t_game *game);
int		handle_movement_keys(int keycode, t_game *game);
int		handle_rotation_keys(int keycode, t_game *game);
int		setup_event_hooks(t_game *game);

/*
Minimap functions. In minimap.c
*/
void	setup_minimap(t_game *game);
void	load_minimap_tiles(t_game *game);
void	generate_full_minimap(t_game *game);
void	render_minimap(t_game *game);
void	draw_minimap_border(t_game *game);
void	draw_triangle_player_indicator(t_game *game, int triangle_x, int triangle_y);
void	cleanup_minimap(t_game *game);

#endif