/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:40:12 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 18:59:06 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Function prototypes
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_mlx_textures(t_game *game);
void	cleanup_mlx_system(t_game *game);

/*
Helper function to cleanup all texture paths.
*/
void	cleanup_texture_paths(t_game *game)
{
	if (game->map.north_texture_path)
		ft_safefree((void **)&game->map.north_texture_path);
	if (game->map.south_texture_path)
		ft_safefree((void **)&game->map.south_texture_path);
	if (game->map.east_texture_path)
		ft_safefree((void **)&game->map.east_texture_path);
	if (game->map.west_texture_path)
		ft_safefree((void **)&game->map.west_texture_path);
	if (game->map.sky_texture_path)
		ft_safefree((void **)&game->map.sky_texture_path);
	if (game->map.floor_texture_path)
		ft_safefree((void **)&game->map.floor_texture_path);
	if (game->map.hdoor_texture_path)
		ft_safefree((void **)&game->map.hdoor_texture_path);
	if (game->map.vdoor_texture_path)
		ft_safefree((void **)&game->map.vdoor_texture_path);
	if (game->map.map_path)
		ft_safefree((void **)&game->map.map_path);
}

/*
Helper function to cleanup map arrays (both main and test maps).
Direct approach for cleaning up both game->map.map and game->map.test_map.
Prevents double-free by explicitly setting pointers to NULL.
*/
void	cleanup_map_array(t_game *game)
{
	size_t	map_len;

	// Cleanup main map
	if (game->map.map)
	{
		map_len = ft_arrlen(game->map.map);
		ft_free_2d(game->map.map, map_len);
		game->map.map = NULL;
	}
	
	// Cleanup test map
	if (game->map.test_map)
	{
		map_len = ft_arrlen(game->map.test_map);
		ft_free_2d(game->map.test_map, map_len);
		game->map.test_map = NULL;
	}
}

/*
Helper function to cleanup MLX textures.
*/
void	cleanup_mlx_textures(t_game *game)
{
	int	i;

	if (game->mlx_ptr)
	{
		if (game->textures.north_wall)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.north_wall);
			game->textures.north_wall = NULL;
		}
		if (game->textures.south_wall)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.south_wall);
			game->textures.south_wall = NULL;
		}
		if (game->textures.east_wall)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.east_wall);
			game->textures.east_wall = NULL;
		}
		if (game->textures.west_wall)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.west_wall);
			game->textures.west_wall = NULL;
		}
		if (game->textures.sky)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.sky);
			game->textures.sky = NULL;
		}
		if (game->textures.floor)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.floor);
			game->textures.floor = NULL;
		}
		if (game->textures.hdoor_frames)
		{
			i = 0;
			while (i < game->textures.hdoor_frame_count)
			{
				if (game->textures.hdoor_frames[i])
					mlx_destroy_image(game->mlx_ptr, game->textures.hdoor_frames[i]);
				i++;
			}
			free(game->textures.hdoor_frames);
			game->textures.hdoor_frames = NULL;
			game->textures.hdoor_frame_count = 0;
		}
		if (game->textures.vdoor_frames)
		{
			i = 0;
			while (i < game->textures.vdoor_frame_count)
			{
				if (game->textures.vdoor_frames[i])
					mlx_destroy_image(game->mlx_ptr, game->textures.vdoor_frames[i]);
				i++;
			}
			free(game->textures.vdoor_frames);
			game->textures.vdoor_frames = NULL;
			game->textures.vdoor_frame_count = 0;
		}
	}
}

/*
Helper function to cleanup MLX system resources.
*/
void	cleanup_mlx_system(t_game *game)
{
	if (game->mlx_ptr)
	{
		if (game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		ft_safefree((void **)&game->mlx_ptr);
	}
}
