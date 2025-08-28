/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:34:42 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 16:28:18 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	cleanup(t_game *game);
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_wall_textures(t_game *game);
void	cleanup_mlx_textures(t_game *game);

/*
Cleanup function to free memory and exit the program.
*/
void	cleanup(t_game *game)
{
	if (!game)
		return ;
	{
		cleanup_map_array(game);
		cleanup_texture_paths(game);
		cleanup_mlx_textures(game);
		cleanup_minimap(game);
		cleanup_mlx_system(game);
		ft_safefree((void **)&game);
	}
	ft_fprintf(2, "Cleanup complete\n");
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
	size_t	i;

	i = 0;
	if (!game || !game->map.map)
		return ;
	if (game->map.map)
	{
		map_len = (game->map.max_rows);
		while (i < (map_len) && game->map.map[i])
		{
			ft_safefree((void **)&game->map.map[i]);
			i++;
		}
	}
	ft_safefree((void **)&game->map.map);
	ft_fprintf(2, "Map array cleanup complete.\n");
}

/*
Helper function to cleanup wall MLX textures.
*/
void	cleanup_wall_textures(t_game *game)
{
	if (game->textures.north_wall && game->textures.north_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.north_wall->img_ptr);
		ft_safefree((void **)&game->textures.north_wall);
	}
	if (game->textures.south_wall && game->textures.south_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.south_wall->img_ptr);
		ft_safefree((void **)&game->textures.south_wall);
	}
	if (game->textures.east_wall && game->textures.east_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.east_wall->img_ptr);
		ft_safefree((void **)&game->textures.east_wall);
	}
	if (game->textures.west_wall && game->textures.west_wall->img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->textures.west_wall->img_ptr);
		ft_safefree((void **)&game->textures.west_wall);
	}
}

/*
Helper function to cleanup MLX textures.
*/
void	cleanup_mlx_textures(t_game *game)
{
	if (!game || !game->mlx_ptr)
		return ;
	{
		cleanup_wall_textures(game);
		if (game->textures.space && game->textures.space->img_ptr)
		{
			mlx_destroy_image(game->mlx_ptr, game->textures.space->img_ptr);
			ft_safefree((void **)&game->textures.space);
		}
		cleanup_door_frames(game);
	}
	ft_safefree((void **)&game->textures);
}
