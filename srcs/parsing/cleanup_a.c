/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:34:42 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 18:13:21 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes (in order)
*/
void	cleanup(t_game *game);
void	cleanup_texture_paths(t_game *game);
void	cleanup_map_array(t_game *game);
void	cleanup_mlx_textures(t_game *game);
void	cleanup_mlx_system(t_game *game);
void	cleanup_minimap(t_game *game);
void	cleanup_door_frames(t_game *game);
int		close_window(t_game *game);
void	cleanup_early(t_game *game, const char *map_path);
void	cleanup_later(t_game *game, const char *map_path);

/*
Cleanup function to free memory and exit the program.
*/
void	cleanup(t_game *game)
{
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	cleanup_mlx_textures(game);
	cleanup_mlx_system(game);
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	ft_safefree((void **)&game);
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

	if (game->map.map)
	{
		map_len = ft_arrlen(game->map.map);
		ft_free_2d(game->map.map, map_len);
	}
}

/*
Helper function to cleanup MLX textures.
*/
void	cleanup_mlx_textures(t_game *game)
{
	if (game->textures.sky)
		mlx_destroy_image(game->mlx_ptr, game->textures.sky);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx_ptr, game->textures.floor);
	if (game->textures.north_wall && game->textures.north_wall->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.north_wall->img_ptr);
	if (game->textures.south_wall && game->textures.south_wall->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.south_wall->img_ptr);
	if (game->textures.east_wall && game->textures.east_wall->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.east_wall->img_ptr);
	if (game->textures.west_wall && game->textures.west_wall->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.west_wall->img_ptr);
	if (game->textures.space && game->textures.space->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures.space->img_ptr);
	cleanup_door_frames(game);
}

/*
Helper function to cleanup MLX system resources.
*/
void	cleanup_mlx_system(t_game *game)
{
	cleanup_minimap(game);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	ft_safefree((void **)&game->mlx_ptr);
}

/*
Helper function to cleanup minimap system resources.
*/
void	cleanup_minimap(t_game *game)
{
	if (game->minimap.wall.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.wall.img_ptr);
	if (game->minimap.floor.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.floor.img_ptr);
	if (game->minimap.door.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.door.img_ptr);
	if (game->minimap.space.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->minimap.space.img_ptr);
	if (game->minimap.full_map_img)
		mlx_destroy_image(game->mlx_ptr, game->minimap.full_map_img);
	if (game->minimap.minimap_img)
		mlx_destroy_image(game->mlx_ptr, game->minimap.minimap_img);
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
Exits the program early if there is an error.
*/
int	close_window(t_game *game)
{
	cleanup_mlx_textures(game);
	cleanup_mlx_system(game);
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	ft_safefree((void **)&game);
	exit(EXIT_SUCCESS);
}

/*
Cleanup if error before mlx initialization.
Handle map array cleanup for validation failures.
*/
void	cleanup_early(t_game *game, const char *map_path)
{
	ft_safefree((void **)&map_path);
	cleanup_mlx_textures(game);
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	ft_safefree((void **)&game);
	exit(1);
}

/*
Cleanup if error after mlx initialization.
*/
void	cleanup_later(t_game *game, const char *map_path)
{
	ft_safefree((void **)&map_path);
	cleanup_mlx_textures(game);
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	cleanup_mlx_system(game);
	ft_safefree((void **)&game);
	exit(1);
}

