/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:34:42 by bleow             #+#    #+#             */
/*   Updated: 2025/08/11 14:09:31 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Function prototypes
int		close_window(t_game *game);
void	cleanup_early(t_game *game);
void	cleanup_later(t_game *game);
void	cleanup(t_game *game);

/*
Cleanup function to free memory and exit the program.
*/
void	cleanup(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	cleanup_mlx_textures(game);
	cleanup_mlx_system(game);
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	ft_safefree((void **)&game);
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
Enhanced to handle map array cleanup for validation failures.
*/
void	cleanup_early(t_game *game)
{
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	ft_safefree((void **)&game);
	exit(1);
}

/*
Cleanup if error after mlx initialization.
*/
void	cleanup_later(t_game *game)
{
	cleanup_mlx_textures(game);
	cleanup_texture_paths(game);
	cleanup_map_array(game);
	cleanup_mlx_system(game);
	ft_safefree((void **)&game);
	exit(1);
}
