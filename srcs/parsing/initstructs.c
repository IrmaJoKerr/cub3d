/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 05:09:28 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes (in order)
*/
void	alloc_and_init_all(t_game **game);
void	init_map_struct(t_map *map);
void	init_texture_struct(t_texture *texture);
void	init_minimap_struct(t_game *game, t_mini *minimap);

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
		ft_fprintf(2, "Error: Failed to allocate memory for game struct.\n");
		exit(EXIT_FAILURE);
	}
	(*game)->curr_x = -1;
	(*game)->curr_y = -1;
	(*game)->view_elevation = -1;
	(*game)->view_direction = -1;
	(*game)->midline = -1;
	while (i < 3)
	{
		(*game)->map.sky_color[i] = -1;
		(*game)->map.floor_color[i] = -1;
		i++;
	}
	init_map_struct(&(*game)->map);
	init_texture_struct(&(*game)->textures);
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
	map->max_cols = 0;
	map->max_rows = 0;
	map->map_start_line = -1;
	map->map_last_line = -1;
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
	texture->north_wall = ft_calloc(1, sizeof(t_image));
	texture->south_wall = ft_calloc(1, sizeof(t_image));
	texture->east_wall = ft_calloc(1, sizeof(t_image));
	texture->west_wall = ft_calloc(1, sizeof(t_image));
	texture->space = ft_calloc(1, sizeof(t_image));
	texture->door_frames = ft_calloc(MAX_DOOR_FRAMES, sizeof(t_image *));
	if (!texture->north_wall || !texture->south_wall || !texture->east_wall
		|| !texture->west_wall || !texture->space || !texture->door_frames)
	{
		ft_fprintf(2, "Error: Failed to allocate memory for textures.");
		exit(EXIT_FAILURE);
	}
	texture->door_frame_count = 0;
}

/*
Initialize the minimap structure with default values and calculate dimensions.
*/
void	init_minimap_struct(t_game *game, t_mini *minimap)
{
	minimap->full_map_img = NULL;
	minimap->full_map_data = NULL;
	minimap->full_map_bpp = 0;
	minimap->full_map_sl = 0;
	minimap->full_map_endian = 0;
	minimap->minimap_img = NULL;
	minimap->minimap_data = NULL;
	minimap->minimap_bpp = 0;
	minimap->minimap_sl = 0;
	minimap->minimap_endian = 0;
	minimap->wall = ft_calloc(1, sizeof(t_image));
	minimap->floor = ft_calloc(1, sizeof(t_image));
	minimap->door = ft_calloc(1, sizeof(t_image));
	minimap->space = ft_calloc(1, sizeof(t_image));
	minimap->width = game->map.max_cols * 20;
	minimap->height = game->map.max_rows * 20;
	minimap->x = 0;
	minimap->y = 0;
}
