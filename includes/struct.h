/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:03:11 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/23 13:05:39 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define SPACE_TEXTURE "textures/space/space.xpm"
# define DOORS_TEXTURE "textures/doors/"
# define TILE_WALL '1'
# define TILE_FLOOR '0'
# define DOOR 'D'
# define TILE_PLAYER "NSEW"
# define VALID_CHARS "01DNSEW"
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define MAX_RGB 255
# define MIN_RGB 0
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05
# define TILE_SIZE 64.0
# define PLAYER_SIZE 16.0
# define PLAYER_RADIUS 24.0
# define MAX_DOOR_FRAMES 8
# define DOOR_ANIM_SPEED 0.1
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define FOV 1.5533
# define MOUSE_SENSITIVITY 0.002
/* 89 degrees in radians. For Norm compliance */

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
	t_door_state	state;
	double			openness;
	int				animation_frame;
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
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	unsigned int	transparent_color;
}	t_image;

typedef struct s_texture
{
	t_image	*north_wall;
	t_image	*south_wall;
	t_image	*east_wall;
	t_image	*west_wall;
	t_image	*space;
	void	*sky;
	void	*floor;
	t_image	**door_frames;
	t_image	*current_door_frames;
	int		door_frame_count;
}	t_texture;

typedef struct s_mini
{
	void	*full_map_img;
	char	*full_map_data;
	int		full_map_bpp;
	int		full_map_sl;
	int		full_map_endian;
	void	*minimap_img;
	char	*minimap_data;
	int		minimap_bpp;
	int		minimap_sl;
	int		minimap_endian;
	t_image	wall;
	t_image	floor;
	t_image	door;
	t_image	space;
	int		full_pixel_width;
	int		full_pixel_height;
	int		x;
	int		y;
}	t_mini;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_texture	textures;
	t_map		map;
	t_image		img;
	t_mini		minimap;
	int			doorcount;
	t_door		*doors;
	double		curr_x;
	double		curr_y;
	double		view_elevation;
	double		view_direction;
	int			midline;
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

// Represents a 2D point.
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// Represents the three vertices of our triangle.
typedef struct s_triangle
{
	t_point	tip;
	t_point	base_l;
	t_point	base_r;
}	t_triangle;

// Holds information needed for drawing pixels.
typedef struct s_draw_info
{
	unsigned int	*pixels;
	int				stride;
}	t_draw_info;

#endif