/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 05:09:40 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "struct.h"
# include "raycasting.h"
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
Tile position calculation functions. In calculate_tile_position.c
*/
// void	init_mlx_sys(t_game *game, const char *map_path); // Remove duplicate, keep correct below
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);
double	tile_center_x(int tile_x);
double	tile_center_y(int tile_y);

/*
Tile movement calculation functions. In tile_move.c
*/
double	calc_move_dx(double view_direction, double speed, int forward);
double	calc_move_dy(double view_direction, double speed, int forward);
double	calc_strafe_dx(double view_direction, double speed, int right);
double	calc_strafe_dy(double view_direction, double speed, int right);
double	calc_distance(double x1, double y1, double x2, double y2);

/*
Angle and elevation calculation functions. In calculate_view.c
*/
double	normalize_angle(double angle);
double	clamp_elevation(double elevation);
void	calc_midline(t_game *game);

/*
Main functions. In cub3D.c
*/
void	init_game(t_game *game, const char *map_file);

/*
Implemented in cub3D.c:
*/
void	init_mlx_sys(t_game *game, const char *map_path);
char	*get_map_path(char *input);
int		check_valid_file_path(char *path);
int	load_texture(t_game *game, t_image *tex, char *path);
int	parse_map_2(const char *file, t_game *game);
int	load_textures(t_game *game);

int		load_door_texture(t_game *game, char *path, int i);
// void	set_player_start_position(t_game *game, int tile_x, int tile_y);

/*
Cleanup functions a. In cleanup_a.c
*/
void	cleanup(t_game *game);
int		close_window(t_game *game);
void	cleanup_early(t_game *game, const char *map_path);
void	cleanup_later(t_game *game, const char *map_path);

/*
Cleanup functions b. In cleanup_b.c
*/
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_mlx_textures(t_game *game);
void	cleanup_mlx_system(t_game *game);
void	cleanup_single_map(char ***map_ptr);
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
void	cleanup_texture_structures(t_game *game);
// int	check_builtin_textures(void); // DEPRECATED
// int	count_door_textures(void); // DEPRECATED
// void	load_all_door_textures(t_game *game); // DEPRECATED
int	flood_fill_validate(t_game *game, char **test_map, int y, int x);
int	check_builtin_textures(t_game *game);
int	is_reachable_space(char c);

/*
Tile coordinate utility functions. In tile_utils.c
*/
int		get_tile_at_position(t_game *game, double x, double y);
bool	is_valid_world_position(t_game *game, double x, double y);
void	set_player_to_tile_center(t_game *game, int tile_x, int tile_y);
bool	is_valid_move(t_game *game, double x, double y);

/*
Path parsing functions. In parse_path.c
*/
void	chk_args(int argc, char **argv);
int		validate_xmp_extension(const char *path);
int		check_valid_texture_path(const char *path);

/*
Parser functions. In parser.c
*/
int		parse_map_1(const char *file, t_game *game);
int		parse_floor_color(char *line, t_game *game);
int		parse_ceiling_color(char *line, t_game *game);

/*
Configuration parser functions. In config_parser.c
*/
// int	parse_configuration_section(const char *file, t_game *game);
int	is_only_whitespace(const char *line);
int	is_map_start_line(const char *line, int *in_map);
int	parse_config_settings(char *line, t_game *game);
int	get_texture_path(char *line, t_game *game, int settings_type);
int	handle_color_settings(char *line, t_game *game, int settings_type);
int	validate_required_config(t_game *game);
int	cleanup_and_return(int fd, char *line, int ret_val);

/*
Parser helper functions. In parser_helpers.c
*/
int		identify_settings_type(const char *line);
char	*extract_texture_path(const char *line, const char *identifier);
int		parse_color_settings(char *line, t_game *game, char settings);
char	*extract_color_values(const char *line, const char *identifier);
int		validate_color_values(const char *values, int color[3]);

/*
Map population functions. In populate_map.c
*/

int	populate_map_array(const char *file, t_game *game);
int	prepare_map_array(t_game *game);
void	copy_line(char *dest, const char *src, int max_cols, int row);
int	skip_to_map(int fd, int map_start_line);
int	fill_map(int fd, t_game *game);

/*
Map parser functions. In map_parser.c
*/
// int		parse_map_section(const char *file, t_game *game, int map_start_line);
int		calc_map_area(int fd, t_game *game, int i);
int	validate_border_line(const char *line);
// int	populate_map_array(const char *file, t_game *game, int map_start_line); // Deprecated or unused
void	count_player_chars(const char *line, t_game *game);
int	validate_interior_line(const char *line);
// void	find_player_position(t_game *game);
int	final_map_validation(t_game *game);

int	validate_map_line_chars(const char *line, t_game *game, int row, int *player_found);

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

#endif