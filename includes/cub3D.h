/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 10:28:30 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <mlx.h>
# include <mlx_int.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

/*
The TILE_WALL, TILE_FLOOR, TILE_DOOR, TILE_PLAYER are 
constants to represent the different types of tiles in the map.
*/
# define TILE_WALL '1'
# define TILE_FLOOR '0'
# define TILE_DOOR 'D'
# define TILE_PLAYER "NSEW"
# define VALID_CHARS "01DNSEW"

typedef enum e_direction
{
	N = 0,
	E = 90,
	S = 180,
	W = 270
}	t_direction;

/*
Structure to hold the map data.
*/
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
	char		*door_texture_path;
	int			resolution[2];
	int			sky_color[3];
	int			floor_color[3];
	int			max_cols;
	int			max_rows;
	t_bool		map_first_wall;
	t_bool		map_last_wall;
	int			herocount;
	int			player_x;
	int			player_y;
	t_direction	start_direction;
}	t_map;

/*
Structure to hold the textures for the game.
*/
typedef struct s_texture
{
	void	*wall;
	void	*floor;
	void	*door;
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
	int			curr_x;
	int			curr_y;
	int			curr_direction;
}	t_game;


void	init_game(t_game *game, const char *map_file);
int		close_window(t_game *game);

/*
In
*/
void	cleanup(t_game *game);
void	cleanup_early(t_game *game);
void	cleanup_later(t_game *game);
void	init_game_st(t_game *game);
void	init_map_st(t_map *map);
void	alloc_and_init_all(t_game **game);
int		is_valid_path(t_game *game, int y, int x);
int		validate_line(char *line, int line_num, t_game *game);
int		validate_chars(char *line, t_game *game, int len);
int		chk_first_and_last_line(char *line);
int		chk_inside_lines(char *line, t_game *game);
int		count_lines(const char *filename);
int		check_counts(t_game *game);
int		check_map_validity(t_game *game);
int		handle_error(t_game *game, char *line, int fd);
int		read_and_validate_lines(int fd, t_game *game);
int		open_map_file(const char *file);
int		allocate_map_memory(t_game *game, int line_count);
int		read_map_line(int fd, char **line);
int		validate_and_store_line(char *line, int line_num, t_game *game);
int		parse_map(const char *file, t_game *game);
void	find_player_pos(t_game *game);
int		final_map_checks(t_game *game);
int		initialize_map(const char *file, t_game *game, int *fd,
			int *line_count);
int		is_collision(int player_x, int player_y, int obj_x, int obj_y);
int		chk_valid_path(const char *full_path);
void	chk_args(int argc, char **argv);
char	*get_map_path(const char *map_file);

#endif