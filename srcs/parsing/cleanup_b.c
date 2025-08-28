/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:40:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 16:27:56 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	cleanup_mlx_system(t_game *game);
void	cleanup_minimap(t_game *game);
void	cleanup_door_frames(t_game *game);
void	cleanup_early(t_game *game, const char *map_path);
void	cleanup_later(t_game *game, const char *map_path);

/*
Helper function to cleanup MLX system resources.
*/
void	cleanup_mlx_system(t_game *game)
{
	if (game->img.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
		game->img.img_ptr = NULL;
	}
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		ft_safefree((void **)&game->mlx_ptr);
	}
}

/*
Helper function to cleanup minimap system resources.
*/
void	cleanup_minimap(t_game *game)
{
	if (game->minimap.wall && game->minimap.wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->minimap.wall->img_ptr);
		ft_safefree((void **)&game->minimap.wall);
	}
	if (game->minimap.floor && game->minimap.floor->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->minimap.floor->img_ptr);
		ft_safefree((void **)&game->minimap.floor);
	}
	if (game->minimap.door && game->minimap.door->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->minimap.door->img_ptr);
		ft_safefree((void **)&game->minimap.door);
	}
	if (game->minimap.space && game->minimap.space->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->minimap.space->img_ptr);
		ft_safefree((void **)&game->minimap.space);
	}
	if (game->minimap.minimap_img)
		mlx_destroy_image(game->mlx_ptr, game->minimap.minimap_img);
	if (game->minimap.full_map_img)
		mlx_destroy_image(game->mlx_ptr, game->minimap.full_map_img);
}

/*
Clean up and free all door frame textures and door data.
*/
void	cleanup_door_frames(t_game *game)
{
	int	i;

	if (game->textures.door_frames)
	{
		i = 0;
		while (i < game->textures.door_frame_count)
		{
			if (game->textures.door_frames[i])
			{
				if (game->textures.door_frames[i]->img_ptr)
				{
					mlx_destroy_image(game->mlx_ptr,
						game->textures.door_frames[i]->img_ptr);
					game->textures.door_frames[i]->img_ptr = NULL;
				}
				ft_safefree((void **)&game->textures.door_frames[i]);
			}
			i++;
		}
		ft_safefree((void **)&game->textures.door_frames);
	}
	if (game->doors)
		ft_safefree((void **)&game->doors);
}

/*
Cleanup if error before mlx initialization.
Handle map array cleanup for validation failures.
*/
void	cleanup_early(t_game *game, const char *map_path)
{
	if (map_path)
		ft_safefree((void **)&map_path);
	if (game)
	{
		if (game->textures.north_wall)
			ft_safefree((void **)&game->textures.north_wall);
		if (game->textures.south_wall)
			ft_safefree((void **)&game->textures.south_wall);
		if (game->textures.east_wall)
			ft_safefree((void **)&game->textures.east_wall);
		if (game->textures.west_wall)
			ft_safefree((void **)&game->textures.west_wall);
		if (game->textures.space)
			ft_safefree((void **)&game->textures.space);
		if (game->textures.door_frames)
			ft_safefree((void **)&game->textures.door_frames);
		cleanup_mlx_textures(game);
		cleanup_texture_paths(game);
		cleanup_map_array(game);
		cleanup_mlx_system(game);
		ft_safefree((void **)&game);
	}
	exit(1);
}

/*
Cleanup if error after mlx initialization.
*/
void	cleanup_later(t_game *game, const char *map_path)
{
	if (map_path)
		ft_safefree((void **)&map_path);
	if (game)
	{
		if (game->textures.north_wall)
			ft_safefree((void **)&game->textures.north_wall);
		if (game->textures.south_wall)
			ft_safefree((void **)&game->textures.south_wall);
		if (game->textures.east_wall)
			ft_safefree((void **)&game->textures.east_wall);
		if (game->textures.west_wall)
			ft_safefree((void **)&game->textures.west_wall);
		if (game->textures.space)
			ft_safefree((void **)&game->textures.space);
		cleanup_door_frames(game);
		cleanup_mlx_textures(game);
		cleanup_texture_paths(game);
		cleanup_map_array(game);
		cleanup_mlx_system(game);
		ft_safefree((void **)&game);
	}
	exit(1);
}
