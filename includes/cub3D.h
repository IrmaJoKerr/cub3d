/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 20:20:39 by bleow            ###   ########.fr       */
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

/*FUNCTIONS IN COLLISIONS FOLDER*/

/*
Tile position calculation functions. In calculate_tile_position.c
*/
int		world_to_tile_x(double x);
int		world_to_tile_y(double y);
bool	is_valid_move(t_game *game, double x, double y);

/*
Angle and elevation calculation functions. In calculate_view.c
*/
double	normalize_angle(double angle);
double	clamp_elevation(double elevation);
void	calc_midline(t_game *game);

/*
Tile movement calculation functions. In tile_move.c
*/
double	calc_move_dx(double view_direction, double speed, int forward);
double	calc_move_dy(double view_direction, double speed, int forward);
double	calc_strafe_dx(double view_direction, double speed, int right);
double	calc_strafe_dy(double view_direction, double speed, int right);

/*FUNCTIONS IN HOOKS FOLDER*/

/*
Handlers for looking/rotation keys (arrow keys). In hooks_look.c
*/
int		handle_rotation_keys(int keycode, t_game *game);
int		press_left(t_game *game);
int		press_right(t_game *game);
int		press_up(t_game *game);
int		press_down(t_game *game);

/*
Mouse movement handling functions. In hooks_mouse.c
*/
int		handle_mouse_move(int x, int y, t_game *game);
void	mouse_delta_calc(int x, int y, t_game *game);

/*
Handlers for movement keys WASD. In hooks_movement.c
*/
int		handle_movement_keys(int keycode, t_game *game);
int		press_w(t_game *game);
int		press_s(t_game *game);
int		press_a(t_game *game);
int		press_d(t_game *game);

/*
Key hook functions. In keyhooks_a.c
*/
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_window_close(t_game *game);
int		handle_mouse_move(int x, int y, t_game *game);
int		setup_event_hooks(t_game *game);

/*FUNCTIONS IN PARSING FOLDER*/

/*
Main functions. In cub3D.c
*/
int		check_builtin_textures(t_game *game);
int		main(int argc, char **argv);
void	init_mlx_sys(t_game *game, const char *map_path);
void	init_game(t_game *game, const char *map_file);

/*
Cleanup functions a. In cleanup_a.c
*/
void	cleanup(t_game *game);
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_wall_textures(t_game *game);
void	cleanup_mlx_textures(t_game *game);

/*
Cleanup functions b. In cleanup_b.c
*/
void	cleanup_mlx_system(t_game *game);
void	cleanup_minimap(t_game *game);
void	cleanup_door_frames(t_game *game);
void	cleanup_early(t_game *game, const char *map_path);
void	cleanup_later(t_game *game, const char *map_path);

/*
Configuration parser functions. In config_parser.c
*/
int		is_only_whitespace(const char *line);
int		parse_config_settings(char *line, t_game *game);
int		handle_color_settings(char *line, t_game *game, int settings_type);
int		validate_required_config(t_game *game);

/*
Initialization functions. In initstructs.c
*/
void	alloc_and_init_all(t_game **game);
void	init_map_struct(t_map *map);
void	init_texture_struct(t_texture *texture);
void	init_minimap_struct(t_game *game, t_mini *minimap);

/*
Texture loading functions. In load_textures.c
*/
int		load_mlx_textures(t_game *game);
int		load_texture(t_game *game, t_image *tex, char *path);
int		load_wall_textures(t_game *game);
int		load_door_texture(t_game *game, char *path, int i);

/*
Map parser functions. In map_parser.c
*/
int		validate_map_line_chars(const char *line, t_game *game,
			int *player_found);
void	set_player_start(t_game *game, char dir);
void	find_player_position(t_game *game);

/*
Map validation utility functions. In map_validation_utils.c
*/
int		get_max_col(char **map, int rows);
int		chk_top_boundary(char *row);
int		chk_bottom_boundary(char *row);
int		chk_row_boundary(char *row, int max_col);

/*
Map validation functions. In map_validation.c
*/
int		is_valid_path(t_game *game, int y, int x);
char	**copy_map_array(char **source_map, int rows);
int		flood_fill_validate(t_game *game, char **test_map, int y, int x);
int		is_reachable_space(char c);
int		validate_map_boundaries(char **map, int rows);

/*
Color extraction and parser functions. In parse_colors.c
*/
int		parse_floor_color(char *line, t_game *game);
int		parse_ceiling_color(char *line, t_game *game);
char	*extract_color_values(const char *line, const char *identifier);
int		chk_color_range(int *converted_colors, int color[3]);
int		validate_color_values(const char *values, int color[3]);

/*
Path parsing functions. In parse_path.c
*/
void	chk_args(int argc, char **argv);
char	*get_map_path(char *input);
int		validate_xmp_extension(const char *path);
char	*build_door_path(int i);

/*
Parsing settings functions. In parse_settings.c
*/
int		identify_settings_type(const char *line);
char	*extract_texture_path(const char *line, const char *identifier);

/*
Texture path parser functions. In parse_texture.c
*/
int		get_texture_path(char *line, t_game *game, int settings_type);
int		check_duplicate_texture(t_game *game, int settings_type);
void	set_texture_path(char *path, t_game *game, int settings_type);
int		check_valid_texture_path(const char *path);

/*
Parser utility functions. In parser_utils.c
*/
int		open_map_file(const char *file);
int		validate_lines_after_map(int fd);
int		calc_map_area(int fd, t_game *game, int i);
int		check_valid_file_path(char *path);

/*
Parser functions. In parser.c
*/
int		parser(const char *file, t_game *game);
int		parse_map_1(int fd, t_game *game);
int		parse_map_2(int fd, t_game *game);
int		find_start_line(const char *line, int *in_map, int *map_start_line,
			int pos);
int		find_end_line(const char *line, int *in_map, int *map_last_line,
			int pos);

/*
Map population functions. In populate_map.c
*/
int		populate_map_array(const char *file, t_game *game);
int		prepare_map_array(t_game *game);
int		skip_to_map(int fd, int map_start_line);
int		fill_map(int fd, t_game *game);
void	verify_print_map(t_game *game);

#endif