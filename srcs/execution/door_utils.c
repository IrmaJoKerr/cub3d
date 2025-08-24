/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 18:47:37 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
bool	count_doors_in_map(t_game *game, int *door_index);
void	init_doors_from_map(t_game *game);
int		get_door_id(t_game *game, int x, int y);
t_image	*get_door_texture(t_game *game, int door_id);

bool	count_doors_in_map(t_game *game, int *door_index)
{
	int	x;
	int	y;

	*door_index = 0;
	fprintf(stderr, "[DEBUG] Counting doors in map.\n");
	fprintf(stderr, "[DEBUG] Map contents:\n");
	y = 0;
	while (y < game->map.max_rows && game->map.map[y])
	{
		fprintf(stderr, "[DEBUG] Row %d: %s\n", y, game->map.map[y]);
		y++;
	}
	fprintf(stderr, "[DEBUG] Finished printing map contents.\n");
	y = 0;
	while (y < game->map.max_rows && game->map.map[y])
	{
		x = 0;
		while (x < game->map.max_cols && game->map.map[y])
		{
			if (game->map.map[y][x] == DOOR)
			{
				(*door_index)++;
				fprintf(stderr, "[DEBUG] Found door at (%d, %d).\n", x, y);
			}
			x++;
		}
		y++;
	}
	fprintf(stderr, "[DEBUG] Total doors counted: %d\n", *door_index);
	game->doorcount = *door_index;
	game->doors = malloc(sizeof(t_door) * game->doorcount);
	if (!game->doors)
	{
		fprintf(stderr, "[DEBUG] Failed to allocate memory for doors array.\n");
		return (false);
	}
	fprintf(stderr, "[DEBUG] Memory allocated for doors array.\n");
	*door_index = 0;
	return (true);
}

/*
Initialize the doors array from the map data.
*/
void	init_doors_from_map(t_game *game)
{
	int	x;
	int	y;
	int	door_index;

	fprintf(stderr, "[DEBUG] Initializing doors from map.\n");
	if (!count_doors_in_map(game, &door_index))
	{
		fprintf(stderr, "[DEBUG] Failed to count doors or allocate memory.\n");
		return ;
	}
	fprintf(stderr, "[DEBUG] Total doors found: %d\n", game->doorcount);
	y = 0;
	while (y < game->map.max_rows)
	{
		x = 0;
		while (x < game->map.max_cols)
		{
			if (game->map.map[y][x] == DOOR)
			{
				fprintf(stderr, "[DEBUG] Initializing door at (%d, %d).\n", x, y);
				game->doors[door_index].x = x;
				game->doors[door_index].y = y;
				game->doors[door_index].state = DOOR_CLOSED;
				game->doors[door_index].openness = 0.0;
				game->doors[door_index].animation_frame = 0;
				door_index++;
			}
			x++;
		}
		y++;
	}
	fprintf(stderr, "[DEBUG] Door initialization complete.\n");
}

/*
Get the door ID for the door at the given map coordinates.
*/
int	get_door_id(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->doorcount)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

/*
Get the texture for the door with the given ID.
*/
t_image	*get_door_texture(t_game *game, int door_id)
{
	t_door	*door;
	int		frame;

	if (door_id < 0 || door_id >= game->doorcount)
		return (game->textures.door_frames[0]);
	door = &game->doors[door_id];
	frame = door->animation_frame;
	if (frame < 0 || frame >= game->textures.door_frame_count)
		frame = 0;
	return (game->textures.door_frames[frame]);
}
