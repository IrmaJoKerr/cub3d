/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/08/11 13:16:58 by wjun-kea         ###   ########.fr       */
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
	game->doors = NULL;
	game->doorcount = 0;
	game->curr_x = 0;
	game->curr_y = 0;
	game->view_direction = 0;
	game->view_elevation = 0;
	game->img.img_ptr = NULL;
	game->img.addr = NULL;
	game->img.bpp = 0;
	game->img.line_len = 0;
	game->img.endian = 0;
}

void	init_texture_st(t_texture *texture)
{
	texture->north_wall = malloc(sizeof(t_image));
	texture->south_wall = malloc(sizeof(t_image));
	texture->east_wall = malloc(sizeof(t_image));
	texture->west_wall = malloc(sizeof(t_image));
	texture->sky = NULL;
	texture->floor = NULL;
	texture->door_frames = malloc(sizeof(t_image*) * MAX_DOOR_FRAMES);
	texture->door_frame_count = 0;
}

/*
Initialises the map struct.
*/
void	init_map_st(t_map *map)
{
	int	i;

	ft_bzero(map, sizeof(*map));
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
