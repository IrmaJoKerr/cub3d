/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 06:27:27 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 18:22:24 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <unistd.h>

/*
Function prototypes
*/
int	load_door_texture(t_game *game, char *path, int i);

/*
Load a door texture and store it in the game struct
*/
int	load_door_texture(t_game *game, char *path, int i)
{
	if (i >= MAX_DOOR_FRAMES)
	{
		return (0);
	}
	game->textures.door_frames[i] = malloc(sizeof(t_image));
	if (!game->textures.door_frames[i])
	{
		return (0);
	}
	usleep(10000); // Add a small delay of 10ms
	if (!path)
	{
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	if (!game->mlx_ptr)
	{
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	if (load_texture(game, game->textures.door_frames[i], path) < 0)
	{
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	game->textures.door_frame_count = i + 1;
	return (1);
}
