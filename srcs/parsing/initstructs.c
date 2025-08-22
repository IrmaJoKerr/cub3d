/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initstructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:41:29 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 14:00:06 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	alloc_and_init_all(t_game **game);

/*
Allocates memory for the game struct.
*/
void	alloc_and_init_all(t_game **game)
{
	int	i;

	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		perror("Error: Failed to allocate memory for game struct.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 3)
	{
		(*game)->map.sky_color[i] = -1;
		(*game)->map.floor_color[i] = -1;
		i++;
	}
	(*game)->map.start_direction = N;
	(*game)->textures.north_wall = ft_calloc(1, sizeof(t_image));
	(*game)->textures.south_wall = ft_calloc(1, sizeof(t_image));
	(*game)->textures.east_wall = ft_calloc(1, sizeof(t_image));
	(*game)->textures.west_wall = ft_calloc(1, sizeof(t_image));
	(*game)->textures.space = ft_calloc(1, sizeof(t_image));
	(*game)->textures.door_frames
		= ft_calloc(MAX_DOOR_FRAMES, sizeof(t_image*));
}
