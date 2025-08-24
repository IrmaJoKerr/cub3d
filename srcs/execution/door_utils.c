/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 16:20:25 by bleow            ###   ########.fr       */
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
	y = 0;
	fprintf(stderr, "[DEBUG] count_doors_in_map: Starting door count\n");
	while (y < game->map.max_rows && game->map.map[y])
	{
		x = 0;
		fprintf(stderr, "[DEBUG] count_doors_in_map: Processing row %d\n", y);
		while (x < game->map.max_cols && game->map.map[y])
		{
			if (game->map.map[y][x] == DOOR)
			{
				(*door_index)++;
				fprintf(stderr, "[DEBUG] count_doors_in_map: Found door at (%d, %d), total doors=%d\n", x, y, *door_index);
			}
			x++;
		}
		y++;
	}
	game->doorcount = *door_index;
	fprintf(stderr, "[DEBUG] count_doors_in_map: Total doors found=%d\n", game->doorcount);
	game->doors = malloc(sizeof(t_door) * game->doorcount);
	if (!game->doors)
	{
		fprintf(stderr, "[ERROR] count_doors_in_map: Failed to allocate memory for doors\n");
		return (false);
	}
	fprintf(stderr, "[DEBUG] count_doors_in_map: Allocated memory for doors at %p\n", (void *)game->doors);
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

	fprintf(stderr, "[DEBUG] init_doors_from_map: Starting initialization\n");
	if (!count_doors_in_map(game, &door_index))
	{
		fprintf(stderr, "[ERROR] init_doors_from_map: Failed to count doors\n");
		return ;
	}
	fprintf(stderr, "[DEBUG] init_doors_from_map: Door count=%d\n", game->doorcount);
	y = 0;
	while (y < game->map.max_rows)
	{
		x = 0;
		fprintf(stderr, "[DEBUG] init_doors_from_map: Processing row %d\n", y);
		while (x < game->map.max_cols)
		{
			if (game->map.map[y][x] == DOOR)
			{
				game->doors[door_index].x = x;
				game->doors[door_index].y = y;
				game->doors[door_index].state = DOOR_CLOSED;
				game->doors[door_index].openness = 0.0;
				game->doors[door_index].animation_frame = 0;
				fprintf(stderr, "[DEBUG] init_doors_from_map: Initialized door at (%d, %d), index=%d\n", x, y, door_index);
				door_index++;
			}
			x++;
		}
		y++;
	}
	fprintf(stderr, "[DEBUG] init_doors_from_map: Initialization complete\n");
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
