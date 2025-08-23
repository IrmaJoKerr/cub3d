/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 17:41:57 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes (in order)
*/
void	alloc_and_init_all(t_game **game);
void	init_map_struct(t_map *map);
void	init_texture_struct(t_texture *texture);
void	init_ray_struct(t_ray *ray);
void	init_game_struct(t_game *game);

/*
Allocates memory for the game struct and initializes members.
*/
void	alloc_and_init_all(t_game **game)
{
	int	i;

	i = 0;
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		perror("Error: Failed to allocate memory for game struct.\n");
		exit(EXIT_FAILURE);
	}
	init_map_struct(&(*game)->map);
	init_texture_struct(&(*game)->textures);
	(*game)->map.start_direction = N;
	while (i < 3)
	{
		(*game)->map.sky_color[i] = -1;
		(*game)->map.floor_color[i] = -1;
		i++;
	}
}

/*
Initializes all members of t_map to safe defaults.
*/
void	init_map_struct(t_map *map)
{
	map->map = NULL;
	map->map_path = NULL;
	map->north_texture_path = NULL;
	map->south_texture_path = NULL;
	map->east_texture_path = NULL;
	map->west_texture_path = NULL;
	map->max_cols = -1;
	map->max_rows = -1;
	map->map_start_line = 0;
	map->map_last_line = 0;
	map->herocount = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->start_direction = N;
}

/*
Initializes all members of t_texture to safe defaults.
*/
void	init_texture_struct(t_texture *texture)
{
	texture->north_wall = NULL;
	texture->south_wall = NULL;
	texture->east_wall = NULL;
	texture->west_wall = NULL;
	texture->space = NULL;
	texture->sky = NULL;
	texture->floor = NULL;
	texture->door_frames = NULL;
	// texture->current_door_frames = NULL; // DEPRECATED, may be needed later
	texture->door_frame_count = 0;
}

void	init_ray_struct(t_ray *ray)
{
	ft_bzero(ray, sizeof(t_ray));
}

/*
Initializes all members of t_game to safe defaults.
*/
void	init_game_struct(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->minimap.full_map_img = NULL;
	game->minimap.minimap_img = NULL;
	game->doorcount = 0;
	game->doors = NULL;
	game->curr_x = -1;
	game->curr_y = -1;
	game->view_elevation = -1;
	game->view_direction = -1;
	game->midline = -1;
}
