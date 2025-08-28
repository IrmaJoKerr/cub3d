/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/26 08:45:33 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
bool	chk_and_alloc_door_mem(t_game *game);
void	init_doors_from_map(t_game *game);
void	add_door_node(t_game *game, int x, int y, int door_index);
int		get_door_id(t_game *game, int x, int y);
t_image	*get_door_texture(t_game *game, int door_id);

/*
Validate and allocate memory for doors.
*/
bool	chk_and_alloc_door_mem(t_game *game)
{
	if (game->doorcount <= 0)
	{
		ft_fprintf(2, "chk_and_alloc_door_mem: No doors to initialize.\n");
		return (false);
	}
	game->doors = ft_calloc(game->doorcount, sizeof(t_door));
	if (!game->doors)
	{
		ft_fprintf(2, "chk_and_alloc_door_mem: Failed to mem alloc.\n");
		return (false);
	}
	return (true);
}

/*
Initialize doors from the map.
*/
void	init_doors_from_map(t_game *game)
{
	int	door_index;
	int	x;
	int	y;

	door_index = -1;
	x = 0;
	y = 0;
	if (!chk_and_alloc_door_mem(game))
		return ;
	while (door_index < game->doorcount - 1)
	{
		if (game->map.map[y][x] == DOOR)
		{
			door_index++;
			add_door_node(game, x, y, door_index);
		}
		x++;
		if (x >= game->map.max_cols)
		{
			x = 0;
			y++;
			if (y >= game->map.max_rows)
				break ;
		}
	}
}

/*
Add a door node to the game.
*/
void	add_door_node(t_game *game, int x, int y, int door_index)
{
	game->doors[door_index].x = x;
	game->doors[door_index].y = y;
	game->doors[door_index].state = DOOR_CLOSED;
	game->doors[door_index].openness = 0.0;
	game->doors[door_index].animation_frame = 0;
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
		{
			return (i);
		}
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
