/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 09:06:19 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_game_st(t_game *game);
void	init_map_st(t_map *map);
void	alloc_and_init_all(t_game **game);

/*
Helper function to initialise the game struct.
*/
void	init_game_st(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->curr_x = 0;
	game->curr_y = 0;
	game->curr_direction = 0;
}

void	init_texture_st(t_texture *texture)
{
	texture->wall = NULL;
	texture->floor = NULL;
	texture->door = NULL;
}

/*
Initialises the map struct.
*/
void	init_map_st(t_map *map)
{
	map->map = NULL;
	map->map_path = NULL;
	map->north_texture_path = NULL;
	map->south_texture_path = NULL;
	map->east_texture_path = NULL;
	map->west_texture_path = NULL;
	map->sky_texture_path = NULL;
	map->floor_texture_path = NULL;
	map->door_texture_path = NULL;
	ft_memset (map->resolution, 0, sizeof(map->resolution));
	ft_memset (map->sky_color, 0, sizeof(map->sky_color));
	ft_memset (map->floor_color, 0, sizeof(map->floor_color));
	map->max_cols = 0;
	map->max_rows = 0;
	map->map_first_wall = FALSE;
	map->map_last_wall = FALSE;
	map->herocount = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->start_direction = N;
}

/*
Allocates memory for the game struct.
*/
void	alloc_and_init_all(t_game **game)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
	{
		perror("Error: Failed to allocate memory for game struct.\n");
		exit(EXIT_FAILURE);
	}
	init_game_st(*game);
	init_map_st(&(*game)->map);
}
