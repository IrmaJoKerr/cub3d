/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 15:38:24 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_game_util(t_game *game);
void	init_map_util(t_map *map);
void	alloc_and_init_all(t_game **game);

/*
Helper function to initialise the game struct.
*/
void	init_game_util(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->curr_x = 0;
	game->curr_y = 0;
}

/*
Initialises the map struct.
*/
void	init_map_util(t_map *map)
{
	map->map = NULL;
	map->max_cols = 0;
	map->max_rows = 0;
	map->map_first_wall = 0;
	map->map_last_wall = 0;
	map->herocount = 0;
	map->hero_x = 0;
	map->hero_y = 0;
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
	init_game_util(*game);
	init_map_util(&(*game)->map);
}
