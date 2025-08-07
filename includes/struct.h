/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:03:11 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/07 16:42:17 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define TILE_WALL '1'
# define TILE_FLOOR '0'
# define HORIZ_DOOR 'H'
# define VERTI_DOOR 'V'
# define TILE_PLAYER "NSEW"
# define VALID_CHARS "01HVNSEW"
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define MAX_RGB 255
# define MIN_RGB 0
# define MOVE_SPEED 5.0
# define ROTATE_SPEED 0.05
# define TILE_SIZE 64.0
// # define PLAYER_SIZE 16.0  // ORPHANED - NEVER USED - COMMENTED OUT FOR TESTING
# define PLAYER_RADIUS 8.0
# define COLL_MARGIN 0.125
# define MAX_DOOR_FRAMES 8
# define DOOR_ANIM_SPEED 0.021
# define DOOR_PROXIMITY_TILES 2.0
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define FOV 1.5533
/* 89 degrees in radians. For Norm compliance */
# define MAX_ELEVATION 0.8727
/* 50 degrees in radians. Maximum up/down look angle */
# define ELEVATION_SPEED 0.05
/* Elevation change per keypress in radians */

# define APPROACH_NORTH 1
# define APPROACH_SOUTH 2
# define APPROACH_EAST 3
# define APPROACH_WEST 4
# define APPROACH_INVALID 0

typedef enum e_direction
{
	N = 0,
	E = 90,
	S = 180,
	W = 270
}	t_direction;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	char			type;
	t_door_state	state;
	double			openness;
	int				animation_frame;
	long			last_attempt_time;
	double			last_attempt_x;
	double			last_attempt_y;
	double			last_attempt_from_x;
	double			last_attempt_from_y;
	int				approach_direction;
}	t_door;

typedef struct s_map
{
	char		**map;
	char		*map_path;
	char		*north_texture_path;
	char		*south_texture_path;
	char		*east_texture_path;
	char		*west_texture_path;
	char		*sky_texture_path;
	char		*floor_texture_path;
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

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_texture
{
	t_image	*north_wall;
	t_image	*south_wall;
	t_image	*east_wall;
	t_image	*west_wall;
	void	*sky;
	void	*floor;
	t_image	**door_frames;
	int		door_frame_count;
}	t_texture;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_texture	textures;
	t_map		map;
	t_image		img;
	t_door		*doors;
	int			doorcount;
	double		curr_x;
	double		curr_y;
	double		view_elevation;
	double		view_direction;
	bool		needs_render;
	long		last_frame_time;
}	t_game;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	int			hit;
	int			side;
	char		hit_tile;
	double		perp_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		cam_x;
}	t_ray;

#endif