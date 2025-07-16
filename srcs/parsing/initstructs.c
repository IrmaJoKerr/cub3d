/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 18:59:06 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	init_texture_st(&game->textures);
	game->curr_x = 0;
	game->curr_y = 0;
	game->view_direction = 0;
	game->view_elevation = 0;
}

void	init_texture_st(t_texture *texture)
{
	texture->north_wall = NULL;
	texture->south_wall = NULL;
	texture->east_wall = NULL;
	texture->west_wall = NULL;
	texture->sky = NULL;
	texture->floor = NULL;
	texture->hdoor_frames = NULL;
	texture->vdoor_frames = NULL;
	texture->hdoor_frame_count = 0;
	texture->vdoor_frame_count = 0;
}

/*
Initialises the map struct.
*/
void	init_map_st(t_map *map)
{
	int	i;

	ft_bzero(map, sizeof(*map));
	i = 0;
	while (i < 2)
	{
		map->resolution[i] = -1;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		map->sky_color[i] = -1;
		map->floor_color[i] = -1;
		i++;
	}
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
