/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 06:27:27 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 01:17:50 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
		ft_fprintf(2, "Error: Too many door textures loaded\n");
		return (0);
	}
	game->textures.door_frames[i] = malloc(sizeof(t_image));
	if (!game->textures.door_frames[i])
	{
		ft_fprintf(2, "Error: Failed to allocate door frame %d\n", i);
		return (0);
	}
	load_texture(game, game->textures.door_frames[i], path);
	game->textures.door_frame_count = i + 1;
	ft_fprintf(2, "Loaded door texture: %s\n", path);
	return (1);
}
