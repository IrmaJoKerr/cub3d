/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/19 03:05:05 by wjun-kea         ###   ########.fr       */
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
void	cleanup_single_map(char ***map_ptr);

/*
Map utility functions. In map_utils.c
*/
char	**copy_map_array(char **source_map, int rows);
int		create_test_map(t_game *game);
void	cleanup_single_map(char ***map_ptr);

/*
Initialization functions. In initstructs.c
*/
void	init_game_st(t_game *game);
void	init_texture_st(t_texture *texture);
void	init_map_st(t_map *map);
void	alloc_and_init_all(t_game **game);

/*
Input validation functions. In input_validation.c
*/
int		validate_line(char *line, int line_num, t_game *game);
int		validate_chars(char *line, t_game *game, int len);
int		chk_first_and_last_line(char *line);
int		chk_inside_lines(char *line, t_game *game);
int		count_lines(const char *filename);

/*
Map validation functions. In map_validation.c
*/
int		is_valid_path(t_game *game, int y, int x);
int		flood_fill_validate(t_game *game, int y, int x);
int		is_reachable_space(char c);

/*
Movement and collision functions. In collisions/movehero.c
*/
int		is_collision(double player_x, double player_y, double obj_x,
			double obj_y);

/*
Tile coordinate utility functions. In tile_utils.c
*/
int		get_tile_at_position(t_game *game, double x, double y);
bool	is_valid_world_position(t_game *game, double x, double y);
void	set_player_to_tile_center(t_game *game, int tile_x, int tile_y);
double	get_tile_center_x(int tile_x);
double	get_tile_center_y(int tile_y);

/*
Tile movement calculation functions. In collisions/tile_move.c
*/
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);
double	tile_to_world_x(int tile_x);
double	tile_to_world_y(int tile_y);
double	tile_center_x(int tile_x);
double	tile_center_y(int tile_y);
double	calc_move_dx(double view_direction, double speed, int forward);
double	calc_move_dy(double view_direction, double speed, int forward);
double	calc_strafe_dx(double view_direction, double speed, int right);
double	calc_strafe_dy(double view_direction, double speed, int right);
bool	is_within_map_bounds(t_game *game, double x, double y);
double	calc_distance(double x1, double y1, double x2, double y2);
double	normalize_angle(double angle);
double	clamp_elevation(double elevation);

/*
Door animation utility functions. In door_utils.c
*/
int		load_door_animation_frames(t_game *game, const char *hdoor_path, 
			const char *vdoor_path);
void	*get_door_frame(t_game *game, char door_type, int frame_index);
void	cleanup_door_frames(t_game *game);

/*
Path parsing functions. In parse_path.c
*/
void	chk_args(int argc, char **argv);

/*
Parser functions. In parser.c
*/
int		open_map_file(const char *file);
int		allocate_map_memory(t_game *game, int line_count);
int		read_map_line(int fd, char **line);
int		validate_and_store_line(char *line, int line_num, t_game *game);
int		parse_map(const char *file, t_game *game);

/*
Parser utility functions a. In parserutil_a.c
*/
void	find_player_pos(t_game *game);
int		final_map_checks(t_game *game);
int		handle_error(t_game *game, char *line, int fd);
int		initialize_map(const char *file, t_game *game, int *fd,
			int *line_count);
int		read_and_validate_lines(int fd, t_game *game);

/*
Parser utility functions b. In parserutil_b.c
*/
int		check_counts(t_game *game);
int		check_map_validity(t_game *game);

/*
Parser utility functions c. In parserutil_c.c
*/
int		parse_configuration(const char *file, t_game *game);
int		parse_settings(char *line, t_game *game);
char	*extract_texture_path(const char *line, const char *identifier);

int		skip_whitespace(const char *str, int start);
int		identify_settings_type(const char *line);
char	*extract_color_values(const char *line, const char *identifier);
char	*extract_resolution_values(const char *line, const char *identifier);
int		parse_color_settings(char *line, t_game *game, char settings);
int		parse_resolution_settings(char *line, t_game *game);
int		validate_color_values(const char *values, int color[3]);
int		validate_resolution_values(const char *values, int resolution[2]);
int		is_valid_number_string(const char *str);

/*
Configuration parser functions. In config_parser.c
*/
int		parse_configuration_section(const char *file, t_game *game);
int		is_only_whitespace(const char *line);
int		is_map_start_line(const char *line);
int		parse_config_settings(char *line, t_game *game);
int		handle_texture_settings(char *line, t_game *game, int settings_type);
int		handle_color_settings(char *line, t_game *game, int settings_type);
int		handle_resolution_settings(char *line, t_game *game);
int		validate_required_config(t_game *game);
int		cleanup_and_return(int fd, char *line, int ret_val);

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

#endif