/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/07 15:41:55 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_doors_from_map(t_game *game)
{
	int x, y, door_index;
	
	// Count doors in map
	game->doorcount = 0;
	y = 0;
	while (y < game->map.max_rows)
	{
		x = 0;
		while (x < game->map.max_cols)
		{
			if (game->map.map[y][x] == HORIZ_DOOR || game->map.map[y][x] == VERTI_DOOR)
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
	while (y < game->map.max_rows)
	{
		x = 0;
		while (x < game->map.max_cols)
		{
			if (game->map.map[y][x] == HORIZ_DOOR || game->map.map[y][x] == VERTI_DOOR)
			{
				printf("🔍 FOUND DOOR: '%c' at tile (%d, %d)\n", game->map.map[y][x], x, y);
				game->doors[door_index].x = x;
				game->doors[door_index].y = y;
				game->doors[door_index].type = game->map.map[y][x];
				game->doors[door_index].state = DOOR_CLOSED;
				game->doors[door_index].openness = 0.0;
				game->doors[door_index].animation_frame = 0;
				game->doors[door_index].last_attempt_time = 0;
				game->doors[door_index].last_attempt_x = -1000.0;
				game->doors[door_index].last_attempt_y = -1000.0;
				game->doors[door_index].last_attempt_from_x = -1000.0;
				game->doors[door_index].last_attempt_from_y = -1000.0;
				door_index++;
			}
			x++;
		}
		y++;
	}
	
	ft_fprintf(1, "✅ Initialized %d doors from map\n", game->doorcount);
	
	// Debug: Print map again after door initialization to check if doors are still there
	fprintf(stderr, "\n🚪 MAP AFTER DOOR INITIALIZATION:\n");
	debug_print_map(game);
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

t_image	*get_door_side_texture(t_game *game, char door_type, int side, double ray_dir_x, double ray_dir_y)
{
	(void)side; // Parameter needed for interface compatibility
	
	if (door_type == VERTI_DOOR)
	{
		// Vertical door: north/south walls on sides
		if (ray_dir_y < 0)
			return (game->textures.north_wall);
		else
			return (game->textures.south_wall);
	}
	else if (door_type == HORIZ_DOOR)
	{
		// Horizontal door: east/west walls on sides
		if (ray_dir_x < 0)
			return (game->textures.west_wall);
		else
			return (game->textures.east_wall);
	}
	return (game->textures.north_wall); // fallback
}

t_image	*get_door_texture(t_game *game, int door_id, int animation_frame)
{
	if (door_id < 0 || door_id >= game->doorcount)
		return (game->textures.door_frames[0]); // fallback
		
	if (animation_frame < 0 || animation_frame >= game->textures.door_frame_count)
		animation_frame = 0;
		
	return (game->textures.door_frames[animation_frame]);
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

// Legacy compatibility functions
int	load_door_animation_frames(t_game *game, const char *hdoor_path, const char *vdoor_path)
{
	(void)game;
	(void)hdoor_path;
	(void)vdoor_path;
	// Door textures are now loaded by default in load_all_door_textures()
	return (1);
}

void	*get_door_frame(t_game *game, char door_type, int frame_index)
{
	(void)door_type;
	if (frame_index >= 0 && frame_index < game->textures.door_frame_count)
		return (game->textures.door_frames[frame_index]);
	return (game->textures.door_frames[0]);
}
