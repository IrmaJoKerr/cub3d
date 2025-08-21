/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:40:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 18:11:23 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Function prototypes
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_mlx_textures(t_game *game);
void	cleanup_mlx_system(t_game *game);
void	clean_wall_textures(t_game *game);

/*
Helper function to cleanup texture structures allocated during initialization.
This function handles the memory allocated in init_texture_st() that is not
dependent on MLX system initialization.
*/
void	cleanup_texture_structures(t_game *game)
{
	if (game->textures.north_wall)
	{
		free(game->textures.north_wall);
		game->textures.north_wall = NULL;
	}
	if (game->textures.south_wall)
	{
		free(game->textures.south_wall);
		game->textures.south_wall = NULL;
	}
	if (game->textures.east_wall)
	{
		free(game->textures.east_wall);
		game->textures.east_wall = NULL;
	}
	if (game->textures.west_wall)
	{
		free(game->textures.west_wall);
		game->textures.west_wall = NULL;
	}
	if (game->textures.door_frames)
	{
		free(game->textures.door_frames);
		game->textures.door_frames = NULL;
	}
}

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
	if (game->map.map_path)
		ft_safefree((void **)&game->map.map_path);
}

/*
Helper function to cleanup map arrays.
Direct approach for cleaning up game->map.map.
Prevents double-free by explicitly setting pointers to NULL.
*/
void	cleanup_map_array(t_game *game)
{
	size_t	map_len;

	if (game->map.map)
	{
		map_len = ft_arrlen(game->map.map);
		ft_free_2d(game->map.map, map_len);
		game->map.map = NULL;
	}
}

/*
Helper function to cleanup wall textures.
*/
void	clean_wall_textures(t_game *game)
{
	if (game->textures.north_wall && game->textures.north_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.north_wall->img_ptr);
		free(game->textures.north_wall);
		game->textures.north_wall = NULL;
	}
	if (game->textures.south_wall && game->textures.south_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.south_wall->img_ptr);
		free(game->textures.south_wall);
		game->textures.south_wall = NULL;
	}
	if (game->textures.east_wall && game->textures.east_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.east_wall->img_ptr);
		free(game->textures.east_wall);
		game->textures.east_wall = NULL;
	}
	if (game->textures.west_wall && game->textures.west_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.west_wall->img_ptr);
		free(game->textures.west_wall);
		game->textures.west_wall = NULL;
	}
}

/*
Helper function to cleanup MLX textures.
*/
void	cleanup_mlx_textures(t_game *game)
{
	if (game->mlx_ptr)
	{
		clean_wall_textures(game);
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
		cleanup_door_frames(game);
	}
}

/*
Helper function to cleanup MLX system resources.
*/
void	cleanup_mlx_system(t_game *game)
{
	if (game->mlx_ptr)
	{
		cleanup_minimap(game);
		if (game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		ft_safefree((void **)&game->mlx_ptr);
	}
}

/*
Helper function to cleanup minimap system resources.
*/
void	cleanup_minimap(t_game *game)
{
	if (!game || !game->mlx_ptr)
		return ;
	if (game->minimap.wall.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.wall.img_ptr);
	if (game->minimap.floor.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.floor.img_ptr);
	if (game->minimap.door.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.door.img_ptr);
	if (game->minimap.full_map_img)
		mlx_destroy_image(game->mlx_ptr, game->minimap.full_map_img);
	if (game->minimap.minimap_img)
		mlx_destroy_image(game->mlx_ptr, game->minimap.minimap_img);
	game->minimap.wall.img_ptr = NULL;
	game->minimap.floor.img_ptr = NULL;
	game->minimap.door.img_ptr = NULL;
	game->minimap.full_map_img = NULL;
	game->minimap.minimap_img = NULL;
	game->minimap.full_map_data = NULL;
	game->minimap.minimap_data = NULL;
	game->minimap.full_width = 0;
	game->minimap.full_height = 0;
	ft_fprintf(1, "✅ Minimap system cleaned up\n");
}
