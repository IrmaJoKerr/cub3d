/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/12 23:22:43 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_doors_from_map(t_game *game)
{
	int x, y, door_index;
	
	// Count doors in map
	game->doorcount = 0;
	y = 0;
	while (y < game->map.max_rows && game->map.map[y])
	{
		x = 0;
		while (x < game->map.max_cols && game->map.map[y])
		{
			if (game->map.map[y][x] == DOOR)
				game->doorcount++;
			x++;
		}
		y++;
	}
	
	if (game->doorcount == 0)
		return;
	
	// Allocate doors array
	game->doors = malloc(sizeof(t_door) * game->doorcount);
	if (!game->doors)
	{
		ft_fprintf(2, "Error: Failed to allocate doors array\n");
		exit(1);
	}
	
	// Initialize doors
	door_index = 0;
	y = 0;
	while (y < game->map.max_rows && game->map.map[y])
	{
		x = 0;
		while (x < game->map.max_cols && game->map.map[y])
		{
			if (game->map.map[y][x] == DOOR)
			{
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
	
	ft_fprintf(1, "✅ Initialized %d doors from map\n", game->doorcount);
}

int	get_door_id(t_game *game, int x, int y)
{
	int i;
	
	i = 0;
	while (i < game->doorcount)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

t_image	*get_door_texture(t_game *game, int door_id)
{
	if (door_id < 0 || door_id >= game->doorcount)
		return (game->textures.door_frames[0]); // fallback

	t_door *door = &game->doors[door_id];
	int frame = door->animation_frame;

	if (frame < 0 || frame >= game->textures.door_frame_count)
		frame = 0;

	return (game->textures.door_frames[frame]);
}

void	cleanup_door_frames(t_game *game)
{
	int i;
	
	if (game->textures.door_frames)
	{
		i = 0;
		while (i < game->textures.door_frame_count)
		{
			if (game->textures.door_frames[i])
			{
				if (game->textures.door_frames[i]->img_ptr)
					mlx_destroy_image(game->mlx_ptr, game->textures.door_frames[i]->img_ptr);
				free(game->textures.door_frames[i]);
			}
			i++;
		}
		free(game->textures.door_frames);
		game->textures.door_frames = NULL;
	}
	
	if (game->doors)
	{
		free(game->doors);
		game->doors = NULL;
	}
}
