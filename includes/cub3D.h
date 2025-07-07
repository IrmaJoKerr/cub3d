/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:59:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 15:38:50 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_printf.h"
# include <mlx.h>
# include <mlx_int.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>

/*
The TILE_WALL, TILE_FLOOR, TILE_DOOR, TILE_HERO are 
constants to represent the different types of tiles in the map.
*/
# define TILE_WALL '1'
# define TILE_FLOOR '0'
# define TILE_DOOR 'D'
# define TILE_HERO 'P'
# define VALID_CHARS "01DP"

/*
Structure to hold the map data.
*/
typedef struct s_map
{
	char		**map;
	int			max_cols;
	int			max_rows;
	int			map_first_wall;
	int			map_last_wall;
	int			herocount;
	int			hero_x;
	int			hero_y;
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
}	t_game;

void	init_game(t_game *game, const char *map_file);
int		close_window(t_game *game);
void	cleanup(t_game *game);
void	cleanup_early(t_game *game);
void	cleanup_later(t_game *game);
void	init_game_util(t_game *game);
void	init_map_util(t_map *map);
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
void	find_hero_position(t_game *game);
int		final_map_checks(t_game *game);
int		initialize_map(const char *file, t_game *game, int *fd,
			int *line_count);
int		is_collision(int hero_x, int hero_y, int obj_x, int obj_y);

#endif