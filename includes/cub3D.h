/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 19:21:49 by bleow            ###   ########.fr       */
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

/*
Map tile character constants for the raycaster engine.
- TILE_WALL: Solid wall character ('1')
- TILE_FLOOR: Empty floor space character ('0')
- HORIZ_DOOR: Horizontal door character ('H')
- VERTI_DOOR: Vertical door character ('V')
- TILE_PLAYER: Valid player starting direction characters ("NSEW")
- VALID_CHARS: All valid map characters for validation ("01HVNSEW")
*/
# define TILE_WALL '1'
# define TILE_FLOOR '0'
# define HORIZ_DOOR 'H'
# define VERTI_DOOR 'V'
# define TILE_PLAYER "NSEW"
# define VALID_CHARS "01HVNSEW"

/*
Display and color validation constants for the graphics system.
- MAX_WIDTH: Maximum allowed screen width (1920 pixels)
- MAX_HEIGHT: Maximum allowed screen height (1080 pixels)
- MAX_RGB: Maximum RGB color value (255)
- MIN_RGB: Minimum RGB color value (0)
*/
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define MAX_RGB 255
# define MIN_RGB 0

/*
Player movement and camera rotation speed constants.
- MOVE_SPEED: Linear movement speed per frame (0.1 units)
- ROTATE_SPEED: Angular rotation speed per frame (0.05 radians)
*/
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05 

/*
Tile-based coordinate system constants for 64x64 pixel tiles.
- TILE_SIZE: Size of each map tile in pixels (64.0)
- PLAYER_SIZE: Player sprite size in pixels (32.0)
- PLAYER_RADIUS: Player collision radius in pixels (16.0)
*/
# define TILE_SIZE 64.0
# define PLAYER_SIZE 32.0
# define PLAYER_RADIUS 16.0

/*
Door animation system constants for animated door frames.
- MAX_DOOR_FRAMES: Maximum number of animation frames per door (8)
- DOOR_ANIM_SPEED: Animation frame timing speed (0.1 seconds per frame)
*/
# define MAX_DOOR_FRAMES 8
# define DOOR_ANIM_SPEED 0.1

/*
Cardinal direction enumeration for player orientation and movement.
- N: North direction (0 degrees)
- E: East direction (90 degrees)
- S: South direction (180 degrees)
- W: West direction (270 degrees)
*/
typedef enum e_direction
{
	N = 0,
	E = 90,
	S = 180,
	W = 270
}	t_direction;

/*
Structure to hold the map data and configuration settings.
- map: 2D array containing the parsed map layout
- test_map: Copy of map used for flood fill validation
- map_path: File path to the .cub map file
- north_texture_path: Path to north wall texture file
- south_texture_path: Path to south wall texture file
- east_texture_path: Path to east wall texture file
- west_texture_path: Path to west wall texture file
- sky_texture_path: Path to ceiling/sky texture file
- floor_texture_path: Path to floor texture file
- hdoor_texture_path: Path to horizontal door texture file
- vdoor_texture_path: Path to vertical door texture file
- resolution: Screen resolution array [width, height]
- sky_color: RGB color values for ceiling [r, g, b]
- floor_color: RGB color values for floor [r, g, b]
- max_cols: Maximum number of columns in the map
- max_rows: Maximum number of rows in the map
- map_first_wall: Boolean flag for first wall validation
- map_last_wall: Boolean flag for last wall validation
- herocount: Number of player spawn points found
- player_x: Player starting X coordinate in world space
- player_y: Player starting Y coordinate in world space
- start_direction: Player initial facing direction (N/S/E/W)
*/
typedef struct s_map
{
	char		**map;
	char		**test_map;
	char		*map_path;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*east_texture_path;
	char		*west_texture_path;
	char		*sky_texture_path;
	char		*floor_texture_path;
	char		*hdoor_texture_path;
	char		*vdoor_texture_path;
	int			resolution[2];
	int			sky_color[3];
	int			floor_color[3];
	int			max_cols;
	int			max_rows;
	bool		map_first_wall;
	bool		map_last_wall;
	int			herocount;
	double		player_x;
	double		player_y;
	t_direction	start_direction;
}	t_map;

/*
Structure to hold the textures for the game.
- north_wall: Texture for north-facing walls
- south_wall: Texture for south-facing walls
- east_wall: Texture for east-facing walls
- west_wall: Texture for west-facing walls
- sky: Texture for ceiling/sky rendering
- floor: Texture for floor rendering
- hdoor_frames: Array of horizontal door animation frames
- vdoor_frames: Array of vertical door animation frames
- hdoor_frame_count: Number of horizontal door frames loaded
- vdoor_frame_count: Number of vertical door frames loaded
*/
typedef struct s_texture
{
	void	*north_wall;
	void	*south_wall;
	void	*east_wall;
	void	*west_wall;
	void	*sky;
	void	*floor;
	void	**hdoor_frames;
	void	**vdoor_frames;
	int		hdoor_frame_count;
	int		vdoor_frame_count;
}	t_texture;

/*
Master structure to hold the game data.
*/
typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_texture	textures;
	t_map		map;
	int			doorcount;
	double		curr_x;
	double		curr_y;
	double		view_elevation;
	double		view_direction;
}	t_game;

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
void	setup_event_hooks(t_game *game);

#endif