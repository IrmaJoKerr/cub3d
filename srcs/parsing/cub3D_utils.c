/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 06:27:27 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 17:43:53 by bleow            ###   ########.fr       */
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
	fprintf(stderr, "[DEBUG] Entering load_door_texture with path: %s, index: %d\n", path, i);
	if (i >= MAX_DOOR_FRAMES)
	{
		fprintf(stderr, "Error: Too many door textures loaded\n");
		return (0);
	}
	fprintf(stderr, "[DEBUG] Allocating memory for door frame %d\n", i);
	game->textures.door_frames[i] = malloc(sizeof(t_image));
	if (!game->textures.door_frames[i])
	{
		fprintf(stderr, "Error: Failed to allocate door frame %d\n", i);
		return (0);
	}
	fprintf(stderr, "[DEBUG] Memory allocated at address: %p\n", (void *)game->textures.door_frames[i]);
	fprintf(stderr, "[DEBUG] Adding delay before loading texture\n");
	usleep(10000); // Add a small delay of 10ms
	fprintf(stderr, "[DEBUG] Loading texture from path: %s\n", path);
	if (!path)
	{
		fprintf(stderr, "Error: Path is NULL\n");
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	if (!game->mlx_ptr)
	{
		fprintf(stderr, "Error: mlx_ptr is NULL\n");
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	fprintf(stderr, "[DEBUG] mlx_ptr address: %p\n", (void *)game->mlx_ptr);
	fprintf(stderr, "[DEBUG] Path: %s\n", path);
	fprintf(stderr, "[DEBUG] Door frame index: %d\n", i);
	fprintf(stderr, "[DEBUG] mlx_ptr address before load_texture: %p\n", (void *)game->mlx_ptr);
	fprintf(stderr, "[DEBUG] door_frames[%d] address: %p\n", i, (void *)game->textures.door_frames[i]);
	if (load_texture(game, game->textures.door_frames[i], path) < 0)
	{
		fprintf(stderr, "Error: Failed to load texture for door frame %d\n", i);
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	game->textures.door_frame_count = i + 1;
	fprintf(stderr, "[DEBUG] Loaded door texture: %s, total frames: %d\n", path, game->textures.door_frame_count);
	return (1);
}
